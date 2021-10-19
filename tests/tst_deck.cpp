#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <map>
#include <memory>

#include "blackjack/card.h"
#include "blackjack/deck.h"
#include "blackjack/generic_player.h"

//------------------------------------------------------------------------------
using ::testing::Return;

//------------------------------------------------------------------------------
class FakeDeck : public Deck {
 public:
  FakeDeck() : Deck() {}

  const CardArray& cards() const { return Hand::cards(); }
};

//------------------------------------------------------------------------------
class MockGenericPlayer : public GenericPlayer {
 public:
  MockGenericPlayer() : GenericPlayer("Player", /*MAXIMUM_CARD_COUNT =*/10) {}
  virtual ~MockGenericPlayer() {}

  const CardArray& cards() const { return Hand::cards(); }

  MOCK_METHOD(bool, isHitting, (), (override));
  MOCK_METHOD(bool, isBoosted, (), (const, override));
};

//------------------------------------------------------------------------------
class TestDeck : public ::testing::Test {
 protected:
  void SetUp() override { deck = std::make_unique<FakeDeck>(); }
  void TearDown() override { deck.reset(nullptr); }

  std::unique_ptr<FakeDeck> deck;
};

//------------------------------------------------------------------------------
std::pair<Card::SuitType, Card::RankType> expectedCard() {
  static int suit = 0;
  static int rank = -1;
  assert(suit < Card::SUITS_COUNT);
  ++rank;
  if (rank >= static_cast<int>(Card::RANK_COUNT)) {
    rank = 0;
    ++suit;
  }
  return std::make_pair<Card::SuitType, Card::RankType>(
      static_cast<Card::SuitType>(suit), static_cast<Card::RankType>(rank));
}

TEST_F(TestDeck, populate) {
  deck->populate();

  const auto& cards(deck->cards());
  ASSERT_EQ(cards.size(), 52);

  auto cards_it(cards.cbegin());
  auto cards_end(cards.cend());
  for (; cards_it != cards_end; ++cards_it) {
    auto actual_card(static_cast<PtrCard>(*cards_it));
    auto expected_card(expectedCard());
    ASSERT_EQ(actual_card->suit(), expected_card.first);
    ASSERT_EQ(actual_card->rank(), expected_card.second);
  }
}

//------------------------------------------------------------------------------
TEST_F(TestDeck, shuffle) {
  deck->populate();
  const auto cards(static_cast<const CardArray&>(deck->cards()));

  deck->shuffle();
  const auto suffled_cards(static_cast<const CardArray&>(deck->cards()));

  auto is_equal =
      std::equal(suffled_cards.cbegin(), suffled_cards.cend(), cards.cbegin());
  ASSERT_FALSE(is_equal);
}

//------------------------------------------------------------------------------
TEST_F(TestDeck, deal) {
  static const int CARDS_COUNT = 52;
  deck->populate();

  for (int it(0); it < CARDS_COUNT; ++it) {
    auto card = deck->deal();
    ASSERT_TRUE(card != nullptr) << "It: " << it;
  }

  auto card = deck->deal();
  ASSERT_TRUE(card == nullptr);
}

//------------------------------------------------------------------------------
TEST_F(TestDeck, additionalCards_boosted) {
  MockGenericPlayer player;

  EXPECT_CALL(player, isBoosted())
      .WillOnce(Return(false))
      .WillOnce(Return(false))
      .WillOnce(Return(false))
      .WillOnce(Return(true))
      .WillOnce(Return(true));
  EXPECT_CALL(player, isHitting()).WillRepeatedly(Return(true));

  deck->populate();
  deck->additionalCards(&player);

  const size_t expected_cards_size = 3u;
  ASSERT_EQ(player.cards().size(), expected_cards_size);
}

//------------------------------------------------------------------------------
TEST_F(TestDeck, additionalCards_hitting) {
  MockGenericPlayer player;

  EXPECT_CALL(player, isHitting())
      .WillOnce(Return(true))
      .WillOnce(Return(true))
      .WillOnce(Return(true))
      .WillOnce(Return(false));
  EXPECT_CALL(player, isBoosted()).WillRepeatedly(Return(false));

  deck->populate();
  deck->additionalCards(&player);

  const size_t expected_cards_size = 3u;
  ASSERT_EQ(player.cards().size(), expected_cards_size);
}
