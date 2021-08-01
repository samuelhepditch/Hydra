#ifndef _GAMEPLAY_H
#define _GAMEPLAY_H
#include "player.h"
#include "deck.h"
#include <vector> 

class Gameplay {
 std::vector<Player> players;
 std::vector<Deck> heads;
 bool didWin(Player player);
 void addPlayers(int numPlayers);
 public:
 void play(int numPlayers);
};

#endif
