#ifndef CARD_H
#define CARD_H

#include <string> 

// Represents a single, abstract card in game. Each card has a 
// value (strength of the card) and a symbol which is a textual 
// human representation of the card. The game expects that each 
// card has a unique score value (always a winner).
class Card {
public:
  // Get card symbol.
  virtual std::string symbol() const = 0;
  
  // Get card value/strength.
  virtual int value() const = 0;
  
  // Compare two cards, which one wins. 
  virtual bool operator > (Card const &otherCard) const {
    return this->value() > otherCard.value();
  }
};

#endif