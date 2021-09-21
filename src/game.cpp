#include "game.h"
//
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>

#include "blackjack/deck.h"
#include "blackjack/house.h"

//------------------------------------------------------------------------------
/** Ожидаемое количество игроков */
static const size_t EXPECTED_PLAYERS_COUNT = 4;
/** Максимальное количество карт */
static const size_t MAXIMUM_CARDS = 52;

//------------------------------------------------------------------------------
Game::Game() {
  m_players.reserve(EXPECTED_PLAYERS_COUNT);
}

//------------------------------------------------------------------------------
Game::~Game() {}

//------------------------------------------------------------------------------
void Game::init(const StringList& names) {
  initPlayers(names);
  initDeck();
  initHouse();
}

//------------------------------------------------------------------------------
void Game::play() {
  initGame();

  /* Скрытие первой карты дилера */
  m_house->flipFirstCard();

  showCards();
  additionalPlayersCards();

  /* Отображение первой карты дилера */
  m_house->flipFirstCard();
  std::cout << std::endl << *m_house;

  additionalHouseCards();
  lookWins();
  clearGame();
}

//------------------------------------------------------------------------------
void Game::initPlayers(const StringList& names) {
  if (names.empty()) {
    throw std::invalid_argument("Список игроков пуст");
  }

  std::transform(names.cbegin(), names.cend(), std::back_inserter(m_players),
                 [](const std::string& player_name) {
                   return Player::createInstance(player_name, MAXIMUM_CARDS);
                 });
}

//------------------------------------------------------------------------------
void Game::initDeck() {
  m_deck = std::make_unique<Deck>();
  m_deck->populate();
  m_deck->shuffle();
}

//------------------------------------------------------------------------------
void Game::initHouse() {
  m_house = std::make_unique<House>(MAXIMUM_CARDS);
}

//------------------------------------------------------------------------------
void Game::initGame() {
  static const int CARDS_COUNT_ON_START_GAME = 2;
  for (int card_it(0); card_it < CARDS_COUNT_ON_START_GAME; ++card_it) {
    for (const auto& player : m_players) {
      player->add(m_deck->deal());
    }
    m_house->add(m_deck->deal());
  }
}

//------------------------------------------------------------------------------
void Game::showCards() {
  for (const auto& player : m_players) {
    std::cout << *player << std::endl;
  }
  std::cout << *m_house << std::endl;
}

//------------------------------------------------------------------------------
void Game::additionalPlayersCards() {
  for (const auto& player : m_players) {
    m_deck->additionalCards(player.get());
  }
}

//------------------------------------------------------------------------------
void Game::additionalHouseCards() {
  m_deck->additionalCards(m_house.get());
}

//------------------------------------------------------------------------------
void Game::lookWins() {
  if (m_house->isBoosted()) {
    findNotBoostedPlayers();
  } else {
    findWinPlayer();
  }
}

//------------------------------------------------------------------------------
void Game::findNotBoostedPlayers() {
  for (const auto& player : m_players) {
    if (player->isBoosted())
      continue;
    else {
      std::cout << player->win() << std::endl;
    }
  }
}

//------------------------------------------------------------------------------
void Game::findWinPlayer() {
  const auto house_value(m_house->value());
  for (const auto& player : m_players) {
    if (player->isBoosted())
      continue;
    else {
      compareValues(*player, house_value);
    }
  }
}

//------------------------------------------------------------------------------
void Game::compareValues(const Player& player, const int houseValue) {
  auto player_value(player.value());
  if (player_value > houseValue) {
    std::cout << player.win() << std::endl;
  } else if (player_value < houseValue) {
    std::cout << player.lose() << std::endl;
  } else {
    std::cout << player.push() << std::endl;
  }
}

//------------------------------------------------------------------------------
void Game::clearGame() {
  std::for_each(m_players.begin(), m_players.end(),
                [](auto player) { player->clear(); });
  m_house->clear();
  m_deck->clear();
}
