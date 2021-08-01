#ifndef _DECK_H_
#define _DECK_H_
#include <vector>
#include <string>

class Deck {
 int deckSize;
 std::vector<std::vector<std::string>> deck;
 void swap(int pos1, int pos2);
 public:
 void shuffle();
 std::vector<std::string> getTopCard();
 void addCard();
 void generateDeck();
 void printDeck();
};

#endif
