#include "deck.h"
#include "player.h"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;


/* returns the size of the deck */
int Deck::getSize(){
  return deck.size();
}


/* clears all cards from the deck */
void Deck::clearDeck() {
  deck.clear();
}

/* swap card in position 1 with card in position 2 */
void Deck::swap(int pos1, int pos2){
  vector<string> tmp = deck[pos1];
  deck[pos1] = deck[pos2];
  deck[pos2] = tmp;
}


/* shuffles the deck by making a random swap 149 times */
void Deck::shuffle(){
  for ( int i = 0; i < (deck.size() * 3); i++ ){
    int pos1 = rand() % deck.size();
    int pos2 = rand() % deck.size();
    swap(pos1,pos2);
  }
}


/* get face value of the passed card */
string Deck::getFaceValue(string card){
  if ( card == "J" ) {
    return "11";
  } else if ( card == "Q" ) {
    return "12";
  } else if ( card == "K" ) {
    return "13";
  } else if ( card == "A" ) {
    return "1";
  } else {
    return card;
  }
}


/* removes the last card in the deck */
void Deck::removeBack() {
  deck.pop_back();
}


std::vector<string> Deck::getCardAt(int pos) {
  return deck[pos];
}

/* returns the last card in the deck */
std::vector<string> Deck::getTopCard(){
  vector<string> card = deck[deck.size() - 1];
  return card;
}


/* adds a card to the front of the deck */
void Deck::addCard(vector<string> card){
    deck.emplace_back(card);
}


/* returns true if passed value is in cardList */
bool Deck::isValidValue(string value) {
  for ( int i = 0; i < cardList.size(); i++ ) {
    if ( value == cardList[i] ) {
      return true; 
    }
  }
  return false;
}


/* returns true if passed value is in suitList */
bool Deck::isValidSuit(string suit) {
  for ( int i = 0; i < suitList.size(); i++ ) {
    if ( suit == suitList[i] ) {
      return true;
    } 
  }
  return false;
}


/* creates a single deck of as many standard 54 card decks as there are players. */
void Deck::generatePlayingCards(int numPlayers){
  for ( int h = 0; h < numPlayers; h++ ) {
    for ( int i = 0; i < cardList.size(); i++ ) {
      for ( int j = 0; j < suitList.size(); j++ ) {
        vector<string> card;
        card.emplace_back(cardList[i]);
        card.emplace_back(suitList[j]);
        card.emplace_back(getFaceValue(cardList[i]));
        deck.emplace_back(card);
      }
    }
    vector<string> joker {"Joker","",""};
    deck.emplace_back(joker);
    deck.emplace_back(joker);
  }
  shuffle();
}


void Deck::distributeCards(vector<Player> &players, int deckSize){
  int index = 0;
  while ( index < deck.size() && index < (deckSize * players.size()) ) {
    for ( int j = 0; j < players.size(); j++ ){
      players[j].addCard(deck[index],"drawPile");
      index += 1;
    }
  }  
}


/* prints the deck, this function is used for debugging purposes */
void Deck::printDeck(){
  for (int i = 0; i < deck.size(); i++) {
    cout << deck[i][0] << deck[i][1] << endl;
  }
}
