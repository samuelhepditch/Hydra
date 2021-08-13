#include "gameplay.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc,char* argv[]){
 cout << "How many players?" << endl;
 string  numPlayers;
 cin >> numPlayers;
 if ( stoi(numPlayers) <= 1 ) {
  cout << "The minimum number of players required for a game of Hydra is 2" << endl;
  return 1;
 }
 Gameplay game;
 if ( argc == 1 ) {
   game.play(stoi(numPlayers));
 } else if (argc == 2) {
   string cmd = argv[1];
   if ( cmd == "-testing" ) {
     cout << endl;
     game.play(stoi(numPlayers),true);
   }
 } else if (argc == 4) {
   string cmd = argv[1];
   string cmd1 = argv[2];
   string cmd2 = argv[3];
   if ( cmd == "-testing" && cmd1 == "-deckSize" ) {
     cout << endl;
     game.play(stoi(numPlayers),true,stoi(cmd2));
   } 
 }
}

