#pragma once

#include <string.h>

#include "blackjack/generic_player.h"

//------------------------------------------------------------------------------
/** Обобщённое представление игрока */
class LIB_BLACKJACK_SHARED House : public GenericPlayer {
 public:
  House(const size_t MAXIMUM_CARD_COUNT);
  virtual ~House();

  virtual bool isHitting() override;

  void flipFirstCard();
};
