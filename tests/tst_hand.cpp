#include <gtest/gtest.h>

#include "blackjack/card.h"
#define private public
#include "blackjack/hand.h"

//------------------------------------------------------------------------------
class TestHand : public ::testing::Test {
 protected:
  void SetUp() override {
    hand = std::make_unique<Hand>(/*MAXIMUM_CARD_COUNT =*/10);
  }
  void TearDown() override { hand.reset(nullptr); }

  int cardSize() const {
    return (hand) ? static_cast<int>(hand->m_cards.size()) : -1;
  }
  const PtrCard getCard(size_t index) const { return hand->m_cards.at(index); }

  std::unique_ptr<Hand> hand;
};

//------------------------------------------------------------------------------
TEST_F(TestHand, add) {
  auto expected_card = Card::createInstance(Card::DIAMONDS, Card::ACE);

  hand->add(expected_card);
  ASSERT_EQ(cardSize(), 1);
  ASSERT_EQ(getCard(0).get(), expected_card.get());
}

//------------------------------------------------------------------------------
TEST_F(TestHand, clear) {
  hand->add(Card::createInstance(Card::DIAMONDS, Card::ACE));
  hand->add(Card::createInstance(Card::DIAMONDS, Card::KING));
  EXPECT_EQ(cardSize(), 2);

  hand->clear();
  ASSERT_EQ(cardSize(), 0);
}

//------------------------------------------------------------------------------
TEST_F(TestHand, value) {
  hand->add(Card::createInstance(Card::DIAMONDS, Card::KING));
  hand->add(Card::createInstance(Card::DIAMONDS, Card::TEN));

  ASSERT_EQ(hand->value(), 20);
}

//------------------------------------------------------------------------------
TEST_F(TestHand, value_ace_and_not_rankcard) {
  hand->add(Card::createInstance(Card::DIAMONDS, Card::NINE));
  hand->add(Card::createInstance(Card::DIAMONDS, Card::ACE));

  ASSERT_EQ(hand->value(), 10);
}

//------------------------------------------------------------------------------
TEST_F(TestHand, value_ace_and_rankcard) {
  hand->add(Card::createInstance(Card::DIAMONDS, Card::KING));
  hand->add(Card::createInstance(Card::DIAMONDS, Card::QUEEN));
  hand->add(Card::createInstance(Card::DIAMONDS, Card::TEN));
  hand->add(Card::createInstance(Card::DIAMONDS, Card::ACE));

  ASSERT_EQ(hand->value(), 41);
}

//------------------------------------------------------------------------------
TEST_F(TestHand, value_two_ace_and_rankcard) {
  hand->add(Card::createInstance(Card::DIAMONDS, Card::KING));
  hand->add(Card::createInstance(Card::DIAMONDS, Card::ACE));
  hand->add(Card::createInstance(Card::CLUBS, Card::ACE));

  ASSERT_EQ(hand->value(), 32);
}
