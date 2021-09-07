#include "blackjack/card.h"

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED Card::Card(SuitType suit, ValueType value)
    : m_suit(suit), m_value(value), m_opened(false) {}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED void Card::setOpened(bool value) {
  m_opened = value;
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED void Card::flip() {
  m_opened = !m_opened;
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED int Card::value() const {
  switch (m_value) {
    case ACE:
      return 1;
    case KING:
    case QUEEN:
    case JACK:
      return 10;
    case TEN:
      return 10;
    case NINE:
      return 9;
    case EIGHT:
      return 8;
    case SEVEN:
      return 7;
    case SIX:
      return 6;
    case FIVE:
      return 5;
    case FOUR:
      return 4;
    case THREE:
      return 3;
    case TWO:
      return 2;
    default:
      break;
  }
  throw std::invalid_argument("Не поддерживаемое значени карты");
}
