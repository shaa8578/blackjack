#include <gtest/gtest.h>

#include "blackjack/card.h"

//------------------------------------------------------------------------------
#define TEST_CARD_IS_NOT_ACE(TYPE)   \
  {                                  \
    Card card(Card::DIAMONDS, TYPE); \
    ASSERT_FALSE(card.isAce());      \
  }

TEST(Test_Card, isAce) {
  {
    Card card(Card::DIAMONDS, Card::ACE);
    ASSERT_TRUE(card.isAce());
  }

  TEST_CARD_IS_NOT_ACE(Card::KING);
  TEST_CARD_IS_NOT_ACE(Card::QUEEN);
  TEST_CARD_IS_NOT_ACE(Card::JACK);
  TEST_CARD_IS_NOT_ACE(Card::TEN);
  TEST_CARD_IS_NOT_ACE(Card::NINE);
  TEST_CARD_IS_NOT_ACE(Card::EIGHT);
  TEST_CARD_IS_NOT_ACE(Card::SEVEN);
  TEST_CARD_IS_NOT_ACE(Card::SIX);
}

//------------------------------------------------------------------------------
#define TEST_CARD_IS_RANK_CARD(TYPE) \
  {                                  \
    Card card(Card::DIAMONDS, TYPE); \
    ASSERT_TRUE(card.isRankCard());  \
  }

#define TEST_CARD_IS_NOT_RANK_CARD(TYPE) \
  {                                      \
    Card card(Card::DIAMONDS, TYPE);     \
    ASSERT_FALSE(card.isRankCard());     \
  }

TEST(Test_Card, isRankCard) {
  TEST_CARD_IS_RANK_CARD(Card::KING);
  TEST_CARD_IS_RANK_CARD(Card::QUEEN);
  TEST_CARD_IS_RANK_CARD(Card::JACK);
  TEST_CARD_IS_NOT_RANK_CARD(Card::ACE);
  TEST_CARD_IS_NOT_RANK_CARD(Card::TEN);
  TEST_CARD_IS_NOT_RANK_CARD(Card::NINE);
  TEST_CARD_IS_NOT_RANK_CARD(Card::EIGHT);
  TEST_CARD_IS_NOT_RANK_CARD(Card::SEVEN);
  TEST_CARD_IS_NOT_RANK_CARD(Card::SIX);
}

//------------------------------------------------------------------------------
#define TEST_CARD_VALUE(TYPE, EXPECTED) \
  {                                     \
    Card card(Card::CLUBS, TYPE);       \
    ASSERT_EQ(card.value(), EXPECTED);  \
  }

TEST(Test_Card, value) {
  TEST_CARD_VALUE(Card::ACE, 1);
  TEST_CARD_VALUE(Card::KING, 10);
  TEST_CARD_VALUE(Card::QUEEN, 10);
  TEST_CARD_VALUE(Card::JACK, 10);
  TEST_CARD_VALUE(Card::TEN, 10);
  TEST_CARD_VALUE(Card::NINE, 9);
  TEST_CARD_VALUE(Card::EIGHT, 8);
  TEST_CARD_VALUE(Card::SEVEN, 7);
  TEST_CARD_VALUE(Card::SIX, 6);
  TEST_CARD_VALUE(Card::FIVE, 5);
  TEST_CARD_VALUE(Card::FOUR, 4);
  TEST_CARD_VALUE(Card::THREE, 3);
  TEST_CARD_VALUE(Card::TWO, 2);
}
