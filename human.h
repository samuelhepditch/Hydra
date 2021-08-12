#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "strategy.h"

class Human: public Strategy {
 public:
 bool determineAction(Player &player, std::vector<Deck> &heads) override; 
};

#endif
