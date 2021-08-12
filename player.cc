#include "player.h"
#include "deck.h"
#include <vector>
#include <string>
#include <iostream>


using namespace std;


/* constructor. */
Player::Player( Strategy *strategy ){
  this->strategy_ = strategy;
};


/* add head to discard pile, create two new heads */
void Player::cutHead(vector<Deck> &heads,vector<string> handPlayed) { 
  addCard(hand,"discardPile");
  if ( reserve.getSize() != 0 ) {
    drawPile.addCard(reserve.getTopCard());
    reserve.removeBack();
  }
  Deck head1;
  Deck head2;
  setHand();
  if ( hand[0] == "Joker" ) {
   hand[0] = "2";
   hand[1] = "J";
   hand[2] = "2"; 
  }
  head1.addCard(playHand());
  heads.emplace_back(head1);
  setHand();
  if ( hand[0] == "Joker" ) {
    hand[0] = "2";
    hand[1] = "J";
    hand[2] = "2";
  }
  head2.addCard(playHand());
  heads.emplace_back(head2);
}


/* returns the discard pile to the draw pile  */
void Player::integrateDiscardPile(){
  drawPile.shuffle();
  int size = discardPile.getSize();
  for ( int i = 0; i < size; i++ ) {
    drawPile.addCard(reserve.getTopCard());
    discardPile.removeBack();
  }  
}


/* return reserve to the top of the drawpile */
void Player::returnReserve(){
  drawPile.addCard(reserve.getTopCard());
  reserve.removeBack();
}

/* assigns a new strategy to this player (human or computer). */
void Player::setStrategy( Strategy *strategy ) {
  delete strategy_;
  strategy_ = strategy;
}


/* executes turn by leveraging a human or computer strategy. */ 
bool Player::executeTurn( vector<Deck> &heads ) {
   return strategy_->determineAction(*this,heads); 
}


/* swaps top card of drawpile with active reserve card, exchange from drawpile to reserve is one way.  */
void Player::swapReserve( vector<string> card ){
  vector<string> tmp;
  if ( reserve.getSize() != 0 ) { 
    tmp = reserve.getTopCard();
    drawPile.addCard(tmp); 
    reserve.removeBack();
  }
  reserve.addCard(card);
}


/* returns the players current hand and removes that card from the drawpile. */
vector<string> Player::playHand(){
  vector<string> cardPlayed = hand;
  hand.clear();
  return cardPlayed;
}


/* picks up top card from a players deck and stores in hand.  */
void Player::setHand() {
  hand = drawPile.getTopCard();
  drawPile.removeBack();
}


/* returns card in players hand. */
vector<string> Player::getHand() {
  return hand;
}


/* */
void Player::print(){
 drawPile.printDeck();
}


/* adds a card to the players deck. */
void Player::addCard( vector<string> card, string deckName ){
  if ( deckName == "drawPile" ) {
    drawPile.addCard(card);
  } else if ( deckName == "discardPile" ){
    discardPile.addCard(card);
  }
}


/* shuffles the specified deck. */
void Player::shuffleDeck(std::string deckName) {
  if ( deckName == "drawPile" ) {
    drawPile.shuffle();
  } else if ( deckName == "discardPile" ){
    discardPile.shuffle();
  }
}


/* returns the size of specified deck (param deckName) */
int Player::getDeckSize( string deckName ) {
  if ( deckName == "drawPile" ) {
    return drawPile.getSize();
  } else if ( deckName == "discardPile" ){
    return discardPile.getSize();
  } else {
    return reserve.getSize();
  }
}
