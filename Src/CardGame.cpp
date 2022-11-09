#include "Card.h"
#include "NumericCard.h"
#include "CardCollection.h"
#include "Player.h"
#include "Game.h"

#include <iostream>

// A simple program using the game engine to play a single game
// between "Red" and "Blue".
int main(int argc, char **argv) {
  std::srand(std::time(0));

  auto deck = CardCollection<NumericCard>::shuffledNumericDeck();
  auto game = Game<NumericCard>(deck);
  
  game.addPlayerWithName("Red");
  game.addPlayerWithName("Blue");
  
  game.start();
  std::cout << "Game started\n";
  
  while(!game.isFinished()) {
    auto roundResult = game.playRound();
    
    std::cout << roundResult.message << ":\n";
    std::cout << "  Cards:" << "\n";
    for (int i = 0; i < roundResult.count; i++) {
      std::cout << "    " << roundResult.players[i] << "(" << 
        roundResult.scores[i] << "pts)"<< " - " << roundResult.cards[i] << "\n";
    }
    std::cout << "\n";
  }
  
  std::cout << "* " << game.gameStatus() << "\n";
  
  return 0;
}