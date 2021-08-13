#ifndef _DECK_H_
#define _DECK_H_

#include <vector>
#include <string>

class Player;

class Deck {
 int deckSize;
 std::vector<std::vector<std::string>> deck;
 void swap(int pos1, int pos2);
 const std::vector<std::string> suitList {"H","D","S","C"};
 const std::vector<std::string> cardList {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
 public:
 void clearDeck();
 std::vector<std::string> getCardAt(int pos);
 static std::string getFaceValue(std::string card);
 void removeBack();
 void shuffle();
 std::vector<std::string> getTopCard();
 void addCard(std::vector<std::string> card);
 void generatePlayingCards(int numPlayers);
 void printDeck();
 void distributeCards(std::vector<Player> &players, int deckSize);
 int getSize();
 bool isValidValue(std::string value);
 bool isValidSuit(std::string suit);
};

#endif
