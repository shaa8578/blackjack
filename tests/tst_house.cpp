#include <gtest/gtest.h>

#include "blackjack/card.h"
#include "blackjack/house.h"

//------------------------------------------------------------------------------
class TestHouse : public ::testing::Test {
 protected:
  void SetUp() override { house = std::make_unique<House>(10); }
  void TearDown() override { house.reset(nullptr); }

  std::unique_ptr<House> house;
};

//------------------------------------------------------------------------------
TEST_F(TestHouse, isHitting) {
  house->add(Card::createInstance(Card::DIAMONDS, Card::KING));
  house->add(Card::createInstance(Card::DIAMONDS, Card::FOUR));

  ASSERT_TRUE(house->isHitting());

  house->add(Card::createInstance(Card::DIAMONDS, Card::TWO));
  ASSERT_TRUE(house->isHitting());

  house->add(Card::createInstance(Card::CLUBS, Card::TWO));
  ASSERT_FALSE(house->isHitting());
}

//------------------------------------------------------------------------------
TEST_F(TestHouse, flipFirstCard) {
  auto first_card(Card::createInstance(Card::DIAMONDS, Card::KING));
  house->add(first_card);

  auto second_card(Card::createInstance(Card::DIAMONDS, Card::FOUR));
  house->add(second_card);

  house->flipFirstCard();

  ASSERT_TRUE(first_card->isOpened());
  ASSERT_FALSE(second_card->isOpened());
}
