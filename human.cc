#include <iostream>
#include "human.h"
#include "deck.h"
#include <vector>
#include "player.h"
#include "strategy.h"

using namespace std;


/* main logic behind a single player turn */
bool Human::determineAction(Player &player,vector<Deck> &heads) {
  vector<string> card = player.playHand(); 
  string headPos;
  cin >> headPos;
  cout << endl;
  if ( stoi(headPos) == 0 ) { 
    player.swapReserve(card);
    return false;
  }
  if ( card[0] == "Joker" ) { 
    cout << "Joker value?" << endl;
    string newVal;
    cin >> newVal;
    card[0] = newVal;
    card[1] = "J";
    card[2] = Deck::getFaceValue(card[0]);
    cout << endl;
  } 
  vector<string> headTop = heads[stoi(headPos) - 1].getTopCard();
  if ( stoi(headTop[2]) >= stoi(card[2]) || stoi(headTop[2]) == 1 ) {
    heads[stoi(headPos) - 1].addCard(card);
    if ( stoi(headTop[2]) == stoi(card[2]) ) { return true; }
  } else {
    for ( int i = 0; i < heads[stoi(headPos) - 1].getSize(); i++ ) {
      player.addCard(heads[stoi(headPos) - 1].getCardAt(i), "discardPile");
    } 
    player.shuffleDeck("discardPile");
    heads[stoi(headPos) - 1].clearDeck();
    player.cutHead(heads,card);
 }
  return false;
}

