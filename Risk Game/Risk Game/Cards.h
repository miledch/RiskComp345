#ifndef CARDS_H
#define CARDS_H
#include <list>
#include <array>

using namespace std;

enum ArmyType { infantry, artillery, cavalry };

class Card {
private:
	ArmyType* cardArmyTypePtr = { nullptr };
	unsigned int cardId;

public:
	static unsigned int nextCardId;
	Card();
	Card(ArmyType);
	ArmyType* getArmyType() const;
	void setArmyType(const ArmyType&);
	int getCardId();
};

class Deck {
private:
	list<Card> allCards;
	list<Card*> deckCards;
	int numOfExchanges{ 0 };
	void generateCards(const int&);
	void initiateDeck();

public:
	int getNumOfExchanges();
	Deck(const int&);
	Card* draw();
	void displayCardsDistribution();
	void exchange(const array<Card*, 3>&);
	list<Card> getAllCards();
};

class Hand {
public:
	Hand(Deck&);
	Hand();
	void draw();
	bool hasExchange() const;
	void displayExchangeOptions() const;
	bool exchange();
	void printCards();
	int getNumHandCards();
	int getNumberOfExchanges();

private:
	void eraseExchangeOptions();
	void addExchangeOptionsOfSameCards(const array<int, 3>&);
	void addExchangeOptionsOfDifferentCards(const array<int, 3>&);
	Deck* gameDeckPtr{ nullptr };
	list<Card*> handCards;
	list<array<Card*, 3>> exchangeOptions;
	void updateExchangeOptions();
};

class CardDriver 
{
public:
	static void run();
};
#endif