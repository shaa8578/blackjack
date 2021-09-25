#include "blackjack/card.h"

#include <assert.h>

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED Card::Card(SuitType suit, RankType value)
    : m_suit(suit), m_rank(value), m_opened(true) {}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED Card::~Card() {}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED
std::shared_ptr<Card> Card::createInstance(Card::SuitType suit,
                                           Card::RankType value) {
  return std::make_shared<Card>(suit, value);
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED void Card::setOpened(bool value) {
  m_opened = value;
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED void Card::flip() {
  m_opened = !m_opened;
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED bool Card::isAce() const {
  return m_rank == ACE;
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED bool Card::isRankCard() const {
  if (m_opened) {
    switch (m_rank) {
      case KING:
      case QUEEN:
      case JACK:
        return true;
      default:
        break;
    }
  }
  return false;
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED int Card::value() const {
  switch (m_rank) {
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

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED std::string Card::toString() const {
  return isOpened() ? (value2String() + suit2String()) : std::string("XX");
}

//------------------------------------------------------------------------------
std::string Card::suit2String() const {
  switch (m_suit) {
    case DIAMONDS:
      return "d";
    case CLUBS:
      return "c";
    case SPADES:
      return "s";
    case HEARTS:
      return "h";
    default:
      break;
  }
  assert(false && "Масть карты не определена");
}

//------------------------------------------------------------------------------
std::string Card::value2String() const {
  switch (m_rank) {
    case ACE:
      return "A";
    case KING:
      return "K";
    case QUEEN:
      return "Q";
    case JACK:
      return "J";
    case TEN:
      return "10";
    case NINE:
      return "9";
    case EIGHT:
      return "8";
    case SEVEN:
      return "7";
    case SIX:
      return "6";
    case FIVE:
      return "5";
    case FOUR:
      return "4";
    case THREE:
      return "3";
    case TWO:
      return "2";
    default:
      break;
  }
  assert(false && "Значение карты не определено");
}
