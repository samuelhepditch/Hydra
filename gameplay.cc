#include "gameplay.h"
#include "player.h"
#include "deck.h"
#include "human.h"
#include "computer.h"
#include <vector>
#include <string> 
#include <iostream>


using namespace std;


/* initializes the list of participants */
void Gameplay::addPlayers(int numPlayers){
  cout << "How many human players?" << endl;
  string numHumanPlayers;
  cin >> numHumanPlayers;
  cout << endl;
  for ( int i = 0; i < numPlayers; i++ ) {
    if ( i < stoi(numHumanPlayers) ) { 
      Human *newHuman = new Human;
      Player newPlayer { newHuman }; 
      players.emplace_back(newPlayer);
    } else {
      Computer *newComputer = new Computer;
      Player newPlayer { newComputer };
      players.emplace_back(newPlayer);
    }
  }
}


/* counts the number of active heads in the game */
int Gameplay::getHeadCount() {
  int headCount = 0;
  for (int i = 0; i < heads.size(); i++) {
    if ( heads[i].getSize() != 0 ) { headCount += 1; }
  }
  return headCount;
}


/* adds players to game, distributes cards to each player, creates initial head. */
void Gameplay::setUp(int numPlayers){
  addPlayers(numPlayers);
  Deck playingCards;
  playingCards.generatePlayingCards(numPlayers);
  playingCards.distributeCards(players);
}


/* prints out all active heads */
void Gameplay::printHeads(){
  cout << "Heads:" << endl;
  for ( int i = 0; i < heads.size(); i++ ){
    if ( heads[i].getSize() != 0 ) {
      vector<string> card  = heads[i].getTopCard();
      cout << i + 1 << ": " << card[0] << card[1] << " (" << heads[i].getSize() << ")" << endl;
    }
  }
  cout << endl;
}


/* prints out all players */
void Gameplay::printPlayers(string type, int turnsTaken) {
  cout << "Players:" << endl;
  for ( int i = 0; i < players.size() ; i++ ) {
    int drawSize = players[i].getDeckSize("drawPile");
    int discardSize = players[i].getDeckSize("discardPile");;
    cout << "Player " << i + 1 << ": " << drawSize + discardSize << " (" << drawSize << " draw, " <<  discardSize << " discard)";
    if ( activePlayer == i && type == "extend" ) {  
      cout << " + 1 in hand, " << getHeadCount() - turnsTaken - 1 << " remaining, ";
      cout << players[i].getDeckSize("Reserve") << " in reserve"; 
    }
    cout << endl;
    if ( i == players.size() - 1 ) { cout << endl; }  
  }
  if ( activePlayer == -1 ) { activePlayer = activePlayer + 2; }
}


/* prints out a statement asking the player to move */
void Gameplay::printMove() {
  players[activePlayer].setHand();
  vector<string> playerHand = players[activePlayer].getHand();
  cout << "Player " << activePlayer + 1 << " you are holding a " << playerHand[0] << playerHand[1] << ". Your move?" << endl;
}


/* determine if player passed has won */
bool Gameplay::didWin(Player &player){
  int cardCount = 0;
  cardCount += player.getDeckSize("drawPile");
  cardCount += player.getDeckSize("discardPile");
  cardCount += player.getDeckSize("reserve");
  if ( cardCount == 0 ) { return true; }
  return false;
}


/* main logic for each game of hydra */
void Gameplay::play(int numPlayers) {
  setUp(numPlayers);
  players[activePlayer + 1].setHand();
  Deck d;
  d.addCard(players[activePlayer + 1].playHand());
  heads.emplace_back(d);
  printHeads();
  printPlayers("basic");
  bool done = false;
  while(!done){
    cout << "Player " << activePlayer + 1 << ", it is your turn." << endl << endl << endl;
    int turnsLeft = getHeadCount();
    int turnsTaken = 0;
    while ( turnsLeft > 0 ) {  
     if ( players[activePlayer + 1].getDeckSize("drawPile") == 0 ) {
        if ( players[activePlayer + 1].getDeckSize("discardPile") != 0 ) {
         players[activePlayer + 1].integrateDiscardPile();
        } else {
         return players[activePlayer + 1].returnReserve();
       }
      }
      printHeads();
      printPlayers("extend",turnsTaken);
      printMove();
      if ( players[activePlayer].executeTurn(heads) ) { break; }
      turnsTaken++;
      turnsLeft = getHeadCount() - turnsTaken;
      if ( didWin(players[activePlayer]) ) { 
        done = true;
        break;
      }
      printHeads();
      printPlayers("basic");
    }
    if ( activePlayer + 1 == numPlayers ) {
      activePlayer = 0;
    }
    else {
      activePlayer += 1;
    };
  }
}


