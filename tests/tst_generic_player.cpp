#include <gtest/gtest.h>

#include <algorithm>
#include <sstream>

#include "blackjack/card.h"
#include "blackjack/generic_player.h"

//------------------------------------------------------------------------------
class FakeGenericPlayer : public GenericPlayer {
 public:
  static const char* PLAYER_NAME;
  explicit FakeGenericPlayer(const std::string& _name)
      : GenericPlayer(_name, /*MAXIMUM_CARD_COUNT =*/10) {}

  const CardArray& cards() const { return GenericPlayer::cards(); }

  virtual bool isHitting() { return false; }
};
const char* FakeGenericPlayer::PLAYER_NAME = "player";

//------------------------------------------------------------------------------
class TestGenericPlayer : public ::testing::Test {
 protected:
  void SetUp() override {
    player =
        std::make_unique<FakeGenericPlayer>(FakeGenericPlayer::PLAYER_NAME);
  }
  void TearDown() override { player.reset(nullptr); }

  std::unique_ptr<FakeGenericPlayer> player;
};

//------------------------------------------------------------------------------
TEST_F(TestGenericPlayer, name) {
  auto player_name = player->name();
  ASSERT_STREQ(player_name.c_str(), FakeGenericPlayer::PLAYER_NAME);
}

//------------------------------------------------------------------------------
TEST_F(TestGenericPlayer, isBoosted) {
  player->add(Card::createInstance(Card::DIAMONDS, Card::KING));
  player->add(Card::createInstance(Card::DIAMONDS, Card::TEN));

  ASSERT_FALSE(player->isBoosted());

  player->add(Card::createInstance(Card::DIAMONDS, Card::SIX));
  ASSERT_TRUE(player->isBoosted());
}

//------------------------------------------------------------------------------
TEST_F(TestGenericPlayer, bust) {
  auto actual_bust(player->bust());
  auto actual_bust_str(actual_bust.c_str());

  ASSERT_STREQ(actual_bust_str, "player - перебор!");
}

//------------------------------------------------------------------------------
TEST_F(TestGenericPlayer, toString) {
  auto actual_empty(player->toString());
  ASSERT_STREQ(actual_empty.c_str(), "player: <empty>");

  player->add(Card::createInstance(Card::DIAMONDS, Card::KING));
  player->add(Card::createInstance(Card::CLUBS, Card::TEN));

  const auto& cards_array(player->cards());
  std::for_each(cards_array.begin(), cards_array.end(),
                [](const PtrCard& card) -> void { card->flip(); });
  auto actual_text(player->toString());
  ASSERT_STREQ(actual_text.c_str(), "player: Kd 10c (20)");
}

//------------------------------------------------------------------------------
TEST_F(TestGenericPlayer, output) {
  player->add(Card::createInstance(Card::DIAMONDS, Card::KING));
  player->add(Card::createInstance(Card::CLUBS, Card::TEN));
  const auto& cards_array(player->cards());
  std::for_each(cards_array.begin(), cards_array.end(),
                [](const PtrCard& card) -> void { card->flip(); });

  std::stringstream ss;
  ss << *player;
  auto actual_text(ss.str());
  ASSERT_STREQ(actual_text.c_str(), "player: Kd 10c (20)");
}
