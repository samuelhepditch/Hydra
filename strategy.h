#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include <vector>
#include "player.h"
#include "deck.h"
#include <string>

class Player;

class Strategy {
 public:
 virtual bool determineAction(Player &player, std::vector<Deck> &heads) = 0;
};

#endif
