#include "blackjack/generic_player.h"

#include <string.h>

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED
GenericPlayer::GenericPlayer(const std::string& _name,
                             const size_t MAXIMUM_CARD_COUNT)
    : Hand(MAXIMUM_CARD_COUNT), m_name(_name) {}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED GenericPlayer::~GenericPlayer() {}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED std::string GenericPlayer::name() const {
  return m_name;
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED bool GenericPlayer::isBoosted() const {
  /** Количество очков, до перебора */
  static const int BOOST_CARDS_VALUE = 21;
  return value() > BOOST_CARDS_VALUE;
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED std::string GenericPlayer::bust() const {
  return m_name + std::string(" - перебор!");
}
