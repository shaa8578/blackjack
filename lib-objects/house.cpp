#include "blackjack/house.h"

#include <vector>

#include "blackjack/card.h"

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED
House::House(const size_t MAXIMUM_CARD_COUNT)
    : GenericPlayer("House", MAXIMUM_CARD_COUNT) {}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED House::~House() {}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED bool House::isHitting() {
  /** Количество карт, после которого дилер отказывается брать карты */
  static const int MAXIMUM_FOR_HITTING = 16;
  return (value() > MAXIMUM_FOR_HITTING) ? false : true;
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED void House::flipFirstCard() {
  const auto& cards(this->cards());
  if (cards.empty()) return;

  auto first_card(cards.front());
  first_card->flip();
}
