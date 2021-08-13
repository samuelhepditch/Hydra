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


/* returns num cards in hand ( 0  or 1 ) */
int Player::handSize(){
  if ( hand.empty() ) return 0;
  return 1;
}

/* add head to discard pile, create two new heads */
void Player::cutHead(vector<Deck> &heads,vector<string> handPlayed, bool testingMode) { 
  discardPile.addCard(handPlayed);
  if ( reserve.getSize() != 0 ) {
    drawPile.addCard(reserve.getTopCard());
    reserve.removeBack();
  }
  Deck head1;
  Deck head2;
  setHand(testingMode);
  if ( hand.empty() == false ) {
    if ( hand[0] == "Joker" ) {
      hand[0] = "2";
      hand[1] = "J";
      hand[2] = "2"; 
    }
    head1.addCard(playHand());
    heads.emplace_back(head1);
  }
  setHand(testingMode);
  if ( hand.empty() == false ) {
    if ( hand[0] == "Joker" ) {
      hand[0] = "2";
      hand[1] = "J";
      hand[2] = "2";
    }
    head2.addCard(playHand());
    heads.emplace_back(head2);
  }
}


/* return reserve to the top of the drawpile */
void Player::returnReserve(){
  if ( reserve.getSize() != 0 ) {
    drawPile.addCard(reserve.getTopCard());
    reserve.removeBack();
  }
}

/* assigns a new strategy to this player (human or computer). */
void Player::setStrategy( Strategy *strategy ) {
  delete strategy_;
  strategy_ = strategy;
}


/* executes turn by leveraging a human or computer strategy. Returns true if player has won. */ 
bool Player::executeTurn(vector<Deck> &heads, int &turnsLeft, bool testingMode) {
   strategy_->determineAction(*this,heads,turnsLeft,testingMode); 
   if ( drawPile.getSize() + discardPile.getSize() + reserve.getSize()  == 0 ) { return true; }
   return false;
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


/* picks up top card from a players deck and stores in hand. */
void Player::setHand(bool testingMode) {
   if ( drawPile.getSize() == 0 ) {
     if ( discardPile.getSize() != 0 ){
       discardPile.shuffle();
       int size = discardPile.getSize();
       for ( int i = 0; i < size; i++ ) {
         drawPile.addCard(discardPile.getTopCard());
         discardPile.removeBack();
       }    
      } else if ( reserve.getSize() != 0 ) {
        drawPile.addCard(reserve.getTopCard());
        reserve.removeBack();
     } else {
       return;
     }
  }
  hand = drawPile.getTopCard();
  if ( testingMode == true ) {
    bool correct = false;
    string val;
    string suit;
    while (!correct) {
     cout << "Card value?" << endl;
     cin >> val;
     if ( drawPile.isValidValue(val) || val == "Joker" ) {
      correct = true;
     }
    }
    if ( val != "Joker") {
     correct = false;
    }
    while(!correct) {
      cout << "Suit?" << endl;
      cin >> suit;
      if ( drawPile.isValidSuit(suit) ) {
        correct = true;
      }
    }
    cout << endl;
    hand[0] = val;
    hand[1] = suit;
    hand[2] = Deck::getFaceValue(val);
  } 
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
