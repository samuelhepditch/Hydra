#include "deck.h"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

/* swap card in position 1 with card in position 2 */
void Deck::swap(int pos1, int pos2){
  vector<string> tmp = deck[pos1];
  deck[pos1] = deck[pos2];
  deck[pos2] = tmp;
}

/* shuffles the deck by making a random swap 149 times */
void Deck::shuffle(){
  for ( int i = 0; i < 150; i++ ){
    int pos1 = rand() % deckSize;
    int pos2 = rand() % deckSize;
    swap(pos1,pos2);
  }
}

/* returns the last card in the deck */
vector<string> Deck::getTopCard(){
  vector<string> topCard = deck[deckSize - 1];
  return topCard;
}

/* adds a card to the front of the deck */
void Deck::addCard(){

}

/* creates a standard deck of 54 cards */
void Deck::generateDeck(){
  vector<string> suitList {"H","D","S","A"};
  vector<string> cardList {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
  for ( int i = 0; i < cardList.size(); i++ ) {
    for ( int j = 0; j < suitList.size(); j++ ) {
      vector<string> card;
      card.emplace_back(cardList[i]);
      card.emplace_back(suitList[j]);
      deck.emplace_back(card);
      deckSize += 1;
    }
  }
  vector<string> joker {"j",""};
  deck.emplace_back(joker);
  deck.emplace_back(joker);
  deckSize += 2;
}

/* prints the deck, this function is used for debugging purposes */
void Deck::printDeck(){
  for (int i = 0; i < deckSize; i++) {
    cout << deck[i][0] << deck[i][1] << endl;
  }
}
