#ifndef GAME_H
#define GAME_H

#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include "CardCollection.h"
#include "RoundResult.h"

// The core engine representing a single game in progress, templated by the
// Card type to use when playing the game. A game is played by creating the object
// with a freshly shuffled deck of cards, calling `start` to initialise the game,
// and subsequently calling `playRound` until game is finished `isFinished`.

template <class T>
class Game {
  // Initial deck of cards to use (give to players).
  CardCollection<T> deck;
  
  // Players participating in the game.
  std::vector<Player<T>> players;
  
  // Current score of the game: mapping players -> number of points.
  std::map<const Player<T> *, int> scoreMap;
  
  // Return a list of player names (first entry - first player).
  const std::vector<std::string> playerNames() const {
    std::vector<std::string> names;
    std::transform(begin(players), end(players), back_inserter(names),
                   [](auto const& player){ return player.name; });
    return names;
  };
  
  // Return a list of player scores (first entry - first player score).
  const std::vector<int> scores() const {
    std::vector<int> scores;
    std::transform(begin(players), end(players), back_inserter(scores),
                   [this](auto const& player){ return scoreMap.at(&player); });
    return scores;
  };
  
public:
  // Initialise with a fresh deck of cards. The cards will be dealt to players on start.
  Game(CardCollection<T> deck): deck(deck) {};
  
  // Return the player currently winning the game or nullptr if nobody wins (draw).
  // The game currently does not support partial winnings in case of 2+ players winning
  // (ie. 2 won, 1 lost is not supported). It's either one clear winner or no winner at all.
  const Player<T>* currentWinner() const {
    // Sort all the players according to scores, top first
    std::vector<const Player<T> *> ranking;
    std::transform(begin(players), end(players), back_inserter(ranking),
                   [](auto const& player){ return &player; });
    std::sort(begin(ranking), end(ranking), 
              [this](const Player<T> *a, const Player<T> *b) {
      return scoreMap.at(a) > scoreMap.at(b);
    });
    
    if (ranking.size() < 2) {
      return ranking.front();
    }
    
    // There are two cases now - either the first won or there is no winner
    // because 2+ players have same score. 
    auto bestScore = scoreMap.at(ranking[0]);
    auto nextScore = scoreMap.at(ranking[1]);
    
    return (bestScore > nextScore) ? ranking.front() : nullptr;    
  }
  
  // Return the current game status which is a message containing player name winning
  // the game (or if there is a draw).
  const std::string gameStatus() const {
    if (auto winner = currentWinner()) {
      return winner->name + " wins the game";
    } else {
      return "There is no winner";
    }
  }
  
  // If the game can continue to be played. The game can continue until all players
  // can continue playing.
  bool isFinished() const {
    for (auto& player : players) { 
      if (!player.canPlay()) {
        return true;
      }
    }
    
    return false;
  }

  // Add a new player to the game with a given name. Players should
  // be added before the game starts.
  void addPlayerWithName(const std::string name) {
    players.push_back(Player<T>(name));
  }

  // Start the game by dealing the cards from the Game's deck to participating
  // players. Should be called before rounds are resolved. Returns the current (initial)
  // status representing the initial round.
  const RoundResult start() {
    // The number of cards each player gets doesn't need to be equal, which is fine
    int cardsIssued = 0;
    while (!this->deck.isEmpty()) {
      auto card = this->deck.drawCard();
      players[cardsIssued % this->players.size()].dealCard(card);
      cardsIssued += 1;
    }
    
    // Reset scores
    for (const auto& player : players) { scoreMap.emplace(&player, 0); };
    
    return RoundResult{ (int) this->players.size(),
                        "Game started",
                        std::vector<std::string>(this->players.size(), "?"), // No cards dealt yet
                        playerNames(), 
                        scores() };
  }
  
  // Play a single round of the game returning the result of the round.
  // This should be called until the game `isFinished`. Calling after game has been finished
  // has undefined behaviour. 
  const RoundResult playRound() {
    // Deal a card for each player collecting the result pairs (Player: Card)
    std::vector<std::pair<Player<T> *, T>> cardsDealt;
    std::transform(begin(players), end(players), back_inserter(cardsDealt),
                   [](auto &player) { 
      auto card = player.drawCard();
      return std::make_pair(&player, card); 
    });
    
    // Find winning max Card returning (Player: Card) combination
    // This bases on assumption cards have unique values. If not, we could sort according to 
    // value and compare first 2 (win/draw).
    auto maxIt = std::max_element(begin(cardsDealt), end(cardsDealt), 
                                  [this](const std::pair<Player<T> *, T> a, const std::pair<Player<T> *, T> b) {
      return !(a.second > b.second);
    });
    auto winner = *maxIt;
    
    // Award the winning player
    scoreMap[winner.first] = scoreMap.at(winner.first) + 1;
    
    // Collect (just) the cards dealt into a single vector
    std::vector<std::string> cards;
    std::transform(begin(cardsDealt), end(cardsDealt), back_inserter(cards),
                   [](auto const& dealing){ return dealing.second.symbol(); });
    
    // Return the results
    return RoundResult{ (int) this->players.size(), 
                        winner.first->name + " wins round",
                        cards, 
                        playerNames(), 
                        scores() };
  }
};

#endif