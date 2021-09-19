#pragma once

#include "blackjack_objects_global.hpp"
//
#include "blackjack/card.h"
#include "blackjack/hand.h"

//------------------------------------------------------------------------------
class GenericPlayer;

//------------------------------------------------------------------------------
/** Колода карт */
class LIB_BLACKJACK_SHARED Deck : public Hand {
 public:
  Deck();
  ~Deck();

  void populate();
  void shuffle();
  PtrCard deal();

  void additionalCards(GenericPlayer* player);
};
