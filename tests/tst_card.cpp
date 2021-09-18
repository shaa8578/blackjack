#include <gtest/gtest.h>

#include "blackjack/card.h"

//------------------------------------------------------------------------------
#define TEST_CARD_VALUE(TYPE, EXPECTED) \
  Card card(Card::CLUBS, TYPE);         \
  ASSERT_EQ(card.value(), EXPECTED);

//------------------------------------------------------------------------------
TEST(Test_Card, value_ACE) {
  TEST_CARD_VALUE(Card::ACE, 1);
}

//------------------------------------------------------------------------------
TEST(Test_Card, value_KING) {
  TEST_CARD_VALUE(Card::KING, 10);
}

//------------------------------------------------------------------------------
TEST(Test_Card, value_QUEEN) {
  TEST_CARD_VALUE(Card::QUEEN, 10);
}

//------------------------------------------------------------------------------
TEST(Test_Card, value_JACK) {
  TEST_CARD_VALUE(Card::JACK, 10);
}

//------------------------------------------------------------------------------
TEST(Test_Card, value_TEN) {
  TEST_CARD_VALUE(Card::TEN, 10);
}

//------------------------------------------------------------------------------
TEST(Test_Card, value_NINE) {
  TEST_CARD_VALUE(Card::NINE, 9);
}

//------------------------------------------------------------------------------
TEST(Test_Card, value_EIGHT) {
  TEST_CARD_VALUE(Card::EIGHT, 8);
}

//------------------------------------------------------------------------------
TEST(Test_Card, value_SEVEN) {
  TEST_CARD_VALUE(Card::SEVEN, 7);
}

//------------------------------------------------------------------------------
TEST(Test_Card, value_SIX) {
  TEST_CARD_VALUE(Card::SIX, 6);
}

//------------------------------------------------------------------------------
TEST(Test_Card, value_FIVE) {
  TEST_CARD_VALUE(Card::FIVE, 5);
}

//------------------------------------------------------------------------------
TEST(Test_Card, value_FOUR) {
  TEST_CARD_VALUE(Card::FOUR, 4);
}

//------------------------------------------------------------------------------
TEST(Test_Card, value_THREE) {
  TEST_CARD_VALUE(Card::THREE, 3);
}

//------------------------------------------------------------------------------
TEST(Test_Card, value_TWO) {
  TEST_CARD_VALUE(Card::TWO, 2);
}
