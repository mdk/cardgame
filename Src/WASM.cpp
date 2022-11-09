#include "Card.h"
#include "NumericCard.h"
#include "CardCollection.h"
#include "Player.h"
#include "Game.h"
#include "RoundResult.h"
#include <emscripten/bind.h>

using namespace emscripten;

// EMScripten bindings for Javascript.
EMSCRIPTEN_BINDINGS(my_module) {
  register_vector<std::string>("StringVector");
  register_vector<int>("IntVector");

  value_object<RoundResult>("RoundResult")
    .field("count", &RoundResult::count)
    .field("message", &RoundResult::message)
    .field("cards", &RoundResult::cards)
    .field("players", &RoundResult::players)
    .field("scores", &RoundResult::scores)
    ;
    
  class_<CardCollection<NumericCard>>("CardCollection")
    .class_function("shuffledNumericDeck", &CardCollection<NumericCard>::shuffledNumericDeck)
    ;
    
  class_<Game<NumericCard>>("Game")
    .constructor<CardCollection<NumericCard>>()
    .function("addPlayerWithName", &Game<NumericCard>::addPlayerWithName)
    .function("start", &Game<NumericCard>::start)
    .function("playRound", &Game<NumericCard>::playRound)
    .function("isFinished", &Game<NumericCard>::isFinished)
    .function("gameStatus", &Game<NumericCard>::gameStatus)
    ;
}