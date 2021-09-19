#pragma once

#include "blackjack_objects_global.hpp"

//------------------------------------------------------------------------------
/** Описание карты в игре БлэкДжек */
class LIB_BLACKJACK_SHARED Card {
 public:
  /** Масть карты */
  enum SuitType {
    DIAMONDS,   /**< Бубы */
    CLUBS,      /**< Трефы */
    SPADES,     /**< Пики */
    HEARTS,     /**< Червы */
    SUITS_COUNT /**< Количество мастей */
  };

  /** Значения карт */
  enum RankType {
    ACE,       /**< Туз */
    KING,      /**< Король */
    QUEEN,     /**< Дами */
    JACK,      /**< Валет */
    TEN,       /**< 10-ка */
    NINE,      /**< 9-ка */
    EIGHT,     /**< 8-ка */
    SEVEN,     /**< 7-ка */
    SIX,       /**< 6-ка */
    FIVE,      /**< 5-ка */
    FOUR,      /**< 6-ка */
    THREE,     /**< 3-ка */
    TWO,       /**< 2-ка */
    RANK_COUNT /**< Количество карт одной масти */
  };

  Card(SuitType suit, RankType value);
  ~Card();

  static std::shared_ptr<Card> createInstance(SuitType suit, RankType value);

  SuitType suit() const { return m_suit; }
  RankType rank() const { return m_rank; }

  bool isOpened() const { return m_opened; }
  void setOpened(bool value);

  void flip();
  bool isAce() const;
  bool isRankCard() const;
  int value() const;

  std::string toString() const;

  bool operator==(const Card& rhs) {
    return (this->m_suit == rhs.m_suit) && (this->m_rank == rhs.m_rank);
  }

  bool operator!=(const Card& rhs) { return !(*this == rhs); }

 protected:
  std::string suit2String() const;
  std::string value2String() const;

 private:
  SuitType m_suit;
  RankType m_rank;
  bool m_opened;
};

//------------------------------------------------------------------------------
template <typename _CharT, typename _Traits>
inline std::basic_ostream<_CharT, _Traits>& operator<<(
    std::basic_ostream<_CharT, _Traits>& os, const Card& card) {
  os << card.toString();
  return os;
}

//------------------------------------------------------------------------------
inline bool operator==(const std::shared_ptr<Card>& lhs,
                       const std::shared_ptr<Card>& rhs) {
  return *lhs == *rhs;
}
