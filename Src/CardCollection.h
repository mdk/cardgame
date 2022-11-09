#ifndef CARD_COLLECTION_H
#define CARD_COLLECTION_H

#include <stack>
#include <vector>
#include <algorithm>
#include <random>
#include "NumericCard.h"

// Represents a collection of cards such as a deck of freshly shuffled cards
// or a pile of cards in a player's possession. Templated with the
// type of card it keeps. 
template <class T>
class CardCollection {
  // Actual collection.
  std::stack<T> cards;
  
public:
  // Create new empty collection.
  CardCollection() {};
  
  // Return true if there are no cards left.
  bool isEmpty() const { return cards.empty(); };

  // Draw/get a topmost card removing it from collection.
  T drawCard() {
    auto card = this->cards.top();
    this->cards.pop();
    return card;
  }
  
  // Give/add a card to the collection. It becomes the topmost card.
  void putCard(T card) {
    this->cards.push(card);
  }
  
  // Helper class method to get a shuffled deck of NumericCards to avoid
  // separate factory.
  static CardCollection<NumericCard> shuffledNumericDeck() {
    // Create a vector of all possible cards in game...
    std::vector<NumericCard> allCards;
    for (int i = 1; i <= NumericCard::NumberOfCards; i++) {
      allCards.push_back(NumericCard(i));
    }

    std::random_device rnd;
    std::mt19937 generator(rnd());    
    std::shuffle(begin(allCards), end(allCards), generator); 
    
    CardCollection<NumericCard> deck;
    for (auto& card : allCards) { deck.putCard(card); };

    /* Alternative implementation: randomly draw from the list 
       and put on top of stack:
        while(!allCards.empty()) {
          int pos = rand() % allCards.size();
          std::vector<NumericCard>::iterator it = allCards.begin();
          std::advance(it, pos);
          deck.putCard(*it);
          allCards.erase(it);
        }
    */
    
    return deck;
  }
};

#endif