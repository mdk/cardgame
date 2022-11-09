#ifndef NUMERIC_CARD_H
#define NUMERIC_CARD_H

#include "Card.h"
#include <stack>
#include <string>

// A specific implementation where the Card has an integer 
// value representing its strength. The cards value is at the
// same time the cards's visual representation (symbol).
class NumericCard: public Card {
  // Strength/number of the card.
  int v;
  
public: 
  // Initialise with given strength/number.
  NumericCard(int v) : v(v) {};

  // Trivial case: card's strength is at the same time it's human
  // representation.
  virtual std::string symbol() const override {
    return std::to_string(this->v);
  }
  
  // Provide card's strength.
  virtual int value() const override {
    return v;
  }
  
  // Number of numeric 1-N cards in the game.
  static constexpr int NumberOfCards = 52;
};

#endif