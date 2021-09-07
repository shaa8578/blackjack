#pragma once

#include "blackjack_objects_global.hpp"

//------------------------------------------------------------------------------
/** Описание карты в игре БлэкДжек */
class LIB_BLACKJACK_SHARED Card {
 public:
  /** Масть карты */
  enum SuitType {
    DIAMONDS, /**< Бубы */
    CLUBS,    /**< Трефы */
    SPADES,   /**< Пики */
    HEARTS    /**< Червы */
  };

  /** Значения карт */
  enum ValueType {
    ACE,   /**< Туз */
    KING,  /**< Король */
    QUEEN, /**< Дами */
    JACK,  /**< Валет */
    TEN,   /**< 10-ка */
    NINE,  /**< 9-ка */
    EIGHT, /**< 8-ка */
    SEVEN, /**< 7-ка */
    SIX,   /**< 6-ка */
    FIVE,  /**< 5-ка */
    FOUR,  /**< 6-ка */
    THREE, /**< 3-ка */
    TWO,   /**< 2-ка */
  };

  Card(SuitType suit, ValueType value);

  SuitType suit() const { return m_suit; }

  bool isOpened() const { return m_opened; }
  void setOpened(bool value);

  void flip();
  int value() const;

 private:
  SuitType m_suit;
  ValueType m_value;
  bool m_opened;
};
