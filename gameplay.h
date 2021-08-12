#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_


#include "player.h"
#include <vector>
#include "deck.h"
#include <string>

class Gameplay {
 void addPlayers(int numPlayers);
 void setUp(int numPlayers);
 void printPlayers(std::string type, int turnsTaken = 0);
 void printMove();
 void printHeads();
 bool didWin(Player &player);
 std::vector<Deck> heads;
 std::vector<Player> players;
 int activePlayer = -1;
 public:
 int getHeadCount();
 void play(int numPlayers);
};


#endif
