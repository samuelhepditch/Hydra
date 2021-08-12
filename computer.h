#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include <vector>
#include <string>
#include "strategy.h"
#include "deck.h"


class Computer: public Strategy {
  public: 
  bool determineAction(Player &player,std::vector<Deck> &heads) override;
};


#endif 
