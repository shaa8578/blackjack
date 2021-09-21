#pragma once

#include <string.h>

#include <memory>
#include <vector>

#include "blackjack/player.h"

//------------------------------------------------------------------------------
class Deck;
class House;

//------------------------------------------------------------------------------
using PtrDeck = std::unique_ptr<Deck>;
using PtrHouse = std::unique_ptr<House>;
using PlayersArray = std::vector<PtrPlayer>;
using StringList = std::vector<std::string>;

//------------------------------------------------------------------------------
/** Основной процесс игры */
class Game {
 public:
  Game();
  ~Game();

  void init(const StringList& names);

  void play();

 private:
  void initPlayers(const StringList& names);
  void initDeck();
  void initHouse();
  void initGame();
  void showCards();
  void additionalPlayersCards();
  void additionalHouseCards();
  void lookWins();
  void findNotBoostedPlayers();
  void findWinPlayer();
  static void compareValues(const Player& player, const int houseValue);
  void clearGame();

 private:
  PtrDeck m_deck;
  PtrHouse m_house;
  PlayersArray m_players;
};
