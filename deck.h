#ifndef _DECK_H_
#define _DECK_H_

#include <vector>
#include <string>

class Player;

class Deck {
 int deckSize;
 std::vector<std::vector<std::string>> deck;
 void swap(int pos1, int pos2);
 public:
 std::vector<std::string> getCardAt(int pos);
 void clearDeck();
 static std::string getFaceValue(std::string card);
 void removeBack();
 void shuffle();
 std::vector<std::string> getTopCard();
 void addCard(std::vector<std::string> card);
 void generatePlayingCards(int numPlayers);
 void printDeck();
 void distributeCards(std::vector<Player> &players);
 int getSize();
};

#endif
