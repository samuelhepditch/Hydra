#include "gameplay.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
 cout << "How many players?" << endl;
 string  numPlayers;
 cin >> numPlayers;
 Gameplay game;
 game.play(stoi(numPlayers));
}
