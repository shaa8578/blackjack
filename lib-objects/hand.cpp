#include "blackjack/hand.h"

#include <numeric>

#include "blackjack/card.h"

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED Hand::Hand(const size_t MAXIMUM_CARD_COUNT) {
  m_cards.reserve(MAXIMUM_CARD_COUNT);
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED Hand::~Hand() {}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED void Hand::add(PtrCard card) {
  m_cards.push_back(card);
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED void Hand::clear() {
  m_cards.clear();
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED int Hand::value() const {
  int ace_count(0);
  bool has_cards_with_rank(false);
  int result(std::accumulate(
      m_cards.begin(), m_cards.end(), 0,
      [&ace_count, &has_cards_with_rank](int init, const PtrCard& card) -> int {
        ace_count += static_cast<int>(card->isAce());
        has_cards_with_rank |= card->isRankCard();
        return init + card->value();
      }));
  if (has_cards_with_rank && (ace_count > 0)) {
    /** Количество очков, добавляемое тузу при наличии старших карт
     *  NOTE: 1 уже добавлен классом Card
     */
    static const int ADD_ACE_VALUE_WITH_RANK_CARDS = 10;
    result += ace_count * ADD_ACE_VALUE_WITH_RANK_CARDS;
  }
  return result;
}

//------------------------------------------------------------------------------
LIB_BLACKJACK_SHARED const CardArray& Hand::cards() const {
  return m_cards;
}
