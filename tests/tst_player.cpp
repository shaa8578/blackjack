#include <gtest/gtest.h>

#include "blackjack/card.h"
#include "blackjack/player.h"

//------------------------------------------------------------------------------
class TestPlayer : public ::testing::Test {
 protected:
  void SetUp() override { player = std::make_unique<Player>("user", 10); }
  void TearDown() override { player.reset(nullptr); }

  std::unique_ptr<Player> player;
};

//------------------------------------------------------------------------------
TEST_F(TestPlayer, win) {
  auto actual(player->win());
  auto actual_str(actual.c_str());

  ASSERT_STREQ(actual_str, "user - выиграл!");
}

//------------------------------------------------------------------------------
TEST_F(TestPlayer, lose) {
  auto actual(player->lose());
  auto actual_str(actual.c_str());

  ASSERT_STREQ(actual_str, "user - проиграл!");
}

//------------------------------------------------------------------------------
TEST_F(TestPlayer, push) {
  auto actual(player->push());
  auto actual_str(actual.c_str());

  ASSERT_STREQ(actual_str, "user сыграл вничью!");
}
