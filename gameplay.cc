#include "gameplay.h"
#include "player.h"


/* initializes the list of participants */
void Gameplay::addPlayers(int numPlayers){
  for ( int i = 0; i < numPlayers; i++ ) {
    Player newPlayer;
    players.emplace_back(newPlayer);
  }
}


/* main logic for each game of hydra */
void Gameplay::play(int numPlayers) {
  addPlayers(numPlayers);
  bool done = false;
  while(!done){
   
  }
}


/* determine if player passed has won */
bool Gameplay::didWin(Player player){
  return true;
}


