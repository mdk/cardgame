#ifndef ROUND_RESULT_H
#define ROUND_RESULT_H

#include <vector>
#include <string>

// A simple structure representing presentable results of a game round
// being played. This is the sort of "view/model" integration layer.
struct RoundResult {
  // Number of entries/players the participated in the round.
  int count;
  
  // Message describing the round results (who won).
  std::string message;
  
  // Vector of player card symbols presented/drawn in this round.
  std::vector<std::string> cards;  
  
  // Vector of player names who participated in this round 
  // (first player = first round).
  std::vector<std::string> players;
  
  // Vector of current game scores after this round has been played 
  // (first player = first score).
  std::vector<int> scores;
};

#endif