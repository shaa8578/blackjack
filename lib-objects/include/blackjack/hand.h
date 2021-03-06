#pragma once

#include <vector>

#include "blackjack_objects_global.hpp"

//------------------------------------------------------------------------------
class Card;
using PtrCard = std::shared_ptr<Card>;
using CardArray = std::vector<PtrCard>;

//------------------------------------------------------------------------------
/** Представляет собой коллекцию карт */
class LIB_BLACKJACK_SHARED Hand {
 public:
  explicit Hand(const size_t MAXIMUM_CARD_COUNT);
  virtual ~Hand();

  void add(PtrCard card);
  void clear();
  int value() const;

 protected:
  const CardArray& cards() const;
  CardArray& cards();

 private:
  /** Вектор указателей на карты */
  CardArray m_cards;
};
