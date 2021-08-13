#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_


#include "player.h"
#include <vector>
#include "deck.h"
#include <string>

class Gameplay {
 void addPlayers(int numPlayers);
 void setUp(int numPlayers, int deckSize);
 void printPlayers(std::string type, int turnsLeft = 0);
 void printMove(bool testingMode);
 void printHeads();
 bool didWin(Player &player);
 std::vector<Deck> heads;
 std::vector<Player> players;
 int activePlayer = -1;
 int getHeadCount();
 public:
 void play(int numPlayers, bool testingMode = false, int deckSize = 54);
};


#endif
