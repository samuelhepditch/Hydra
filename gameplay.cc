#include "gameplay.h"
#include "player.h"
#include "deck.h"
#include "human.h"
#include <vector>
#include <string> 
#include <iostream>


using namespace std;


/* initializes the list of participants */
void Gameplay::addPlayers(int numPlayers){
  for ( int i = 0; i < numPlayers; i++ ) {
    Human *newHuman = new Human;
    Player newPlayer { newHuman }; 
    players.emplace_back(newPlayer);
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
void Gameplay::setUp(int numPlayers,int deckSize){
  addPlayers(numPlayers);
  Deck playingCards;
  playingCards.generatePlayingCards(numPlayers);
  playingCards.distributeCards(players,deckSize);;
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
void Gameplay::printPlayers(string type, int turnsLeft) {
  cout << "Players:" << endl;
  for ( int i = 0; i < players.size(); i++ ) {
    int drawSize = players[i].getDeckSize("drawPile");
    int discardSize = players[i].getDeckSize("discardPile");;
    cout << "Player " << i + 1 << ": " << drawSize + discardSize << " (" << drawSize << " draw, " <<  discardSize << " discard)";
    if ( activePlayer == i && type == "extend" ) {  
      cout << " + " << players[i].handSize() << "  in hand, " << turnsLeft - 1 << " remaining, ";
      cout << players[i].getDeckSize("Reserve") << " in reserve"; 
    }
    cout << endl;
    if ( i == players.size() - 1 ) { cout << endl; }  
  }
  if ( activePlayer == -1 ) { activePlayer = activePlayer + 2; }
}


/* prints out a statement asking the player to move */
void Gameplay::printMove(bool testingMode) {
  players[activePlayer].setHand(testingMode);
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
void Gameplay::play(int numPlayers, bool testingMode, int deckSize) {
  setUp(numPlayers,deckSize);
  players[activePlayer + 1].setHand(testingMode);
  Deck d;
  d.addCard(players[activePlayer + 1].playHand());
  heads.emplace_back(d);
  printHeads();
  printPlayers("basic");
  bool done = false;
  while(!done){
    cout << "Player " << activePlayer + 1 << ", it is your turn." << endl << endl << endl;
    int turnsLeft = getHeadCount();
    while ( turnsLeft > 0 ) {  
      printHeads();
      printPlayers("extend",turnsLeft);
      printMove(testingMode);
      if ( players[activePlayer].executeTurn(heads,turnsLeft,testingMode) ) {
        done = true;
        break;
      }
      printHeads();
      printPlayers("basic");
    }
    players[activePlayer].returnReserve();
    if ( activePlayer + 1 == numPlayers ) {
      activePlayer = 0;
    }
    else {
      activePlayer += 1;
    };
  }
  cout << "Player " << activePlayer + 1 << " wins!" << endl;
}


