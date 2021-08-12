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
   void cutHead(std::vector<Deck> &heads,std::vector<std::string> handPlayed);
   Player(Strategy *strategy = nullptr);
   void setStrategy( Strategy *strategy);
   bool executeTurn(std::vector<Deck> &heads); 
   void swapReserve(std::vector<std::string> card );
   void setHandsPlayed(int val);
   int getHandsPlayed();
   std::vector<std::string> playHand();
   void setHand();
   std::vector<std::string> getHand();
   void addCard(std::vector<std::string> card, std::string deckName);
   void shuffleDeck(std::string deckName);
   int getDeckSize(std::string deckName); 
   void print();
   void integrateDiscardPile();
   void returnReserve(); 
};

#endif
