#pragma once

#include <string.h>

#include "blackjack/generic_player.h"

//------------------------------------------------------------------------------
class Player;
using PtrPlayer = std::shared_ptr<Player>;

//------------------------------------------------------------------------------
/** Обобщённое представление игрока */
class LIB_BLACKJACK_SHARED Player : public GenericPlayer {
 public:
  Player(const std::string& _name, const size_t MAXIMUM_CARD_COUNT);
  virtual ~Player();

  virtual bool isHitting() override;

  std::string win() const;
  std::string lose() const;
  std::string push() const;

  static PtrPlayer createInstance(const std::string& _name,
                                  const size_t MAXIMUM_CARD_COUNT);
};
