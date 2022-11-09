#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "CardCollection.h"

// Represents a single player participating in a game.
template <class T>
class Player {
  // The cards in players possession.
  CardCollection<T> hand;

public:
  // Name of the player.
  const std::string name;

  // Initialise a new player object with an empty hand.
  Player(const std::string name) : name(name) {}

  // If the player can continue playing. The player can continue until
  // he has at least one card to participate in next round.
  bool canPlay() const { return !hand.isEmpty(); }

  // Deal (give) the player a given card to hand. The card is placed on 
  // top of player's hand (fifo).
  void dealCard(T card) {
    hand.putCard(card);
  }
  
  // Draw (get) the topmost card from the Player's hand.
  T drawCard() {
    return hand.drawCard();
  }
};

#endif