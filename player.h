#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include <string>
#include "strategy.h"
#include "deck.h"

class Strategy;

class Player {
   Strategy *strategy_;
   std::vector<std::string> hand;
   Deck drawPile;
   Deck discardPile;
   Deck reserve;
   public:
   int handSize();
   std::vector<std::string> playHand();
   void setHand(bool testingMode);
   std::vector<std::string> getHand();
   void addCard(std::vector<std::string> card, std::string deckName);
   void shuffleDeck(std::string deckName); 
   void print();
   void returnReserve(); 
   void integrateDiscardPile();
   int getDeckSize(std::string deckName);
   void setHandsPlayed(int val);
   int getHandsPlayed();
   bool executeTurn(std::vector<Deck> &heads, int &turnsLeft, bool testingMode);
   Player(Strategy *strategy = nullptr);
   void setStrategy( Strategy *strategy);
   void swapReserve(std::vector<std::string> card );
   void cutHead(std::vector<Deck> &heads,std::vector<std::string> handPlayed, bool testingMode);
};

#endif
