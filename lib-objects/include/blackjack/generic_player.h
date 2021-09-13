#pragma once

#include <string.h>

#include "blackjack/hand.h"

//------------------------------------------------------------------------------
/** Обобщённое представление игрока */
class LIB_BLACKJACK_SHARED GenericPlayer : public Hand {
 public:
  GenericPlayer(const std::string& _name, const size_t MAXIMUM_CARD_COUNT);
  virtual ~GenericPlayer();

  std::string name() const;

  virtual bool isHitting() = 0;
  bool isBoosted() const;

  std::string bust() const;
  std::string toString() const;

 private:
  std::string m_name;
};

//------------------------------------------------------------------------------
template <typename _CharT, typename _Traits>
inline std::basic_ostream<_CharT, _Traits>& operator<<(
    std::basic_ostream<_CharT, _Traits>& os, const GenericPlayer& gp) {
  os << gp.toString();
  return os;
}
