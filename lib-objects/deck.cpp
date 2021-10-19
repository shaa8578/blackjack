#include "blackjack/deck.h"
//
#include <algorithm>
#include <iostream>
#include <random>

#include "blackjack/generic_player.h"

//------------------------------------------------------------------------------
static const int DECK_MAXIMUM_CARD_COUNT = 52;

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED Deck::Deck() : Hand(DECK_MAXIMUM_CARD_COUNT) {}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED Deck::~Deck() {}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED void Deck::populate() {
  clear();
  for (int suit = 0; suit < Card::SUITS_COUNT; ++suit) {
    for (int rank = 0; rank < Card::RANK_COUNT; ++rank) {
      add(Card::createInstance(static_cast<Card::SuitType>(suit),
                               static_cast<Card::RankType>(rank)));
    }
  }
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED void Deck::shuffle() {
  CardArray& cards = Hand::cards();
  std::shuffle(cards.begin(), cards.end(),
               std::mt19937{std::random_device{}()});
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED PtrCard Deck::deal() {
  CardArray& deck_cards = Hand::cards();
  PtrCard result(nullptr);
  if (deck_cards.empty() == false) {
    result = deck_cards.back();
    deck_cards.pop_back();
  }
  return result;
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED void Deck::additionalCards(GenericPlayer* player) {
  std::cout << std::endl;
  while ((player->isBoosted() == false) && (player->isHitting())) {
    player->add(deal());
    std::cout << *player << std::endl;
  }
  if (player->isBoosted()) {
    std::cout << player->bust() << std::endl;
  }
}
