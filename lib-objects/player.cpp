#include "blackjack/player.h"

#include <string.h>

#include <iostream>
#include <limits>

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED
Player::Player(const std::string& _name, const size_t MAXIMUM_CARD_COUNT)
    : GenericPlayer(_name, MAXIMUM_CARD_COUNT) {}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED Player::~Player() {}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED bool Player::isHitting() {
  char user_answer(0);
  while (true) {
    std::cout << "Нужна ещё одна карта (y/n)? " << std::ends;
    std::cin >> user_answer;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    } else {
      if (user_answer == 'y' || user_answer == 'n') {
        break;
      }
    }
    std::cerr << "Необходимо ввести символы 'y', или 'n'" << std::endl;
  }
  return (user_answer == 'y');
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED std::string Player::win() const {
  return name() + std::string(" - выиграл!");
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED std::string Player::lose() const {
  return name() + std::string(" - проиграл!");
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED std::string Player::push() const {
  return name() + std::string(" сыграл вничью!");
}
