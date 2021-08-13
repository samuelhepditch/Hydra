#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "strategy.h"

class Human: public Strategy {
 public:
 void determineAction(Player &player, std::vector<Deck> &heads, int &turnsLeft, bool testingMode) override; 
};

#endif
