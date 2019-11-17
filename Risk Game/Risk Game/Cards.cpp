#include "Cards.h"
#include <random>
#include <ctime>
#include <iostream>

using namespace std;

unsigned int Card::nextCardId = 1;// used to assign ID with each created card 

ArmyType infantryCard = ArmyType::infantry;
ArmyType artilleryCard = ArmyType::artillery;
ArmyType cavalryCard = ArmyType::cavalry;
// constructor assign infantry as defualt and increment the Id number by one, 
Card::Card()
{
	this->cardId = nextCardId++;
	this->cardArmyTypePtr = &infantryCard;
}
// constructor to assign specific ArmyType to created card and it calls the Card() first
Card::Card(ArmyType at) : Card()
{
	setArmyType(at);
}
// to get the ArmyType pointer of a card
ArmyType* Card::getArmyType() const
{
	return this->cardArmyTypePtr;
}
// to set the ArmyType pointer of a card
void Card::setArmyType(const ArmyType& at)
{
	if (at == ArmyType::infantry)
		this->cardArmyTypePtr = &infantryCard;
	else if (at == ArmyType::artillery)
		this->cardArmyTypePtr = &artilleryCard;
	else
		this->cardArmyTypePtr = &cavalryCard;
}
// to get the ID of a card 
int Card::getCardId()
{
	return this->cardId;
}
//deck constructor used the number of counties in the map to create equal number of cards in the Deck
Deck::Deck(const int& numberOfCountries)
{
	srand((unsigned int)time(NULL));
	this->generateCards(numberOfCountries);
	this->initiateDeck();
}

// create the Deck with fair equal number of each ArmyType 
void Deck::generateCards(const int& numberOfCountries)
{
	array<int, 3> armyTypeSize;
	armyTypeSize[0] = (numberOfCountries / 3) + ((numberOfCountries % 3) / 2);
	armyTypeSize[1] = (numberOfCountries / 3) + +((numberOfCountries % 3) / 2);
	armyTypeSize[2] = numberOfCountries - armyTypeSize[0] - armyTypeSize[1];

	for (int t = 0; t < numberOfCountries; ++t) {

		int cardArmyType = rand() % 3;

		while (armyTypeSize[cardArmyType] == 0) {
			if (cardArmyType == 2) {
				cardArmyType = 0;
			}
			else
				cardArmyType += 1;
		}

		if (cardArmyType == 0)
			allCards.push_back(Card());
		else if (cardArmyType == 1)
			allCards.push_back(Card(ArmyType::artillery));
		else
			allCards.push_back(Card(ArmyType::cavalry));

		armyTypeSize[cardArmyType] -= 1;
	}
}
// create a list of pointer to each card in the deck 
void Deck::initiateDeck()
{
	for (list<Card>::iterator it = allCards.begin(); it != allCards.end(); ++it) {
		Card* cardPtr = &*it;
		list<Card*>::iterator currentCard = deckCards.insert(deckCards.end(), cardPtr);
	}
}
//draw a pointer of card randomly from the deckCards which is a list of pointers , and return that pointer and erase it from the deckCards list
Card* Deck::draw()
{
	int randCard = (rand() % deckCards.size()) + 1;
	list<Card*>::iterator cardIt = deckCards.begin();
	for (int t = 1; t < randCard; ++t) {
		cardIt++;
	}
	Card* selectedCard = *cardIt;
	deckCards.erase(cardIt);
	return &*selectedCard;
}
// display Cards Distribution by showing how many pointers are pointing to each type
void Deck::displayCardsDistribution()
{
	int infantryCardsCount{ 0 };
	int artilleryCardsCount{ 0 };
	int cavalryCardsCount{ 0 };

	for (auto cardIt = this->allCards.begin(); cardIt != allCards.end(); ++cardIt) {
		if (*cardIt->getArmyType() == ArmyType::artillery)
			++artilleryCardsCount;
		else if (*cardIt->getArmyType() == ArmyType::cavalry)
			++cavalryCardsCount;
		else
			++infantryCardsCount;
	}

	cout << "Infantry Cards Count: " << infantryCardsCount << endl;
	cout << "Artillery Cards Count: " << artilleryCardsCount << endl;
	cout << "Cavalry Cards Count: " << cavalryCardsCount << endl;
}
//exchange an array of pointers of three matched cards
void Deck::exchange(const array<Card*, 3> & exchangedCards)
{// for lop to insert all the pointers(card pointers) in the array in the deck
	for (size_t t{ 0 }; t < exchangedCards.size(); ++t) {
		int insertAt = (rand() % this->deckCards.size() + 1);
		auto cardIt = deckCards.begin();
		for (int x{ 0 }; x < insertAt; ++x) {
			++cardIt;
		}
		deckCards.insert(cardIt, exchangedCards[t]);
	}
	// printing the number of soldiers awarded for trading in number of cards
	cout << "The rewarded soldiers are " << ++this->numOfExchanges * 5 << endl;
}
list<Card> Deck::getAllCards()
{
	return this->allCards;
}
//hand constructor points the hand to +++++
Hand::Hand(Deck& d)
{
	this->gameDeckPtr = &d;
}
Hand::Hand()
{
	gameDeckPtr = new Deck(0);
}

//draw a pointer cards from the gameDeck and isnsert it in the hand(list of card pointers)
void Hand::draw()
{
	this->handCards.insert(this->handCards.end(), gameDeckPtr->draw());
	this->updateExchangeOptions();
}
//check how many card we have from each type in the hand 
void Hand::updateExchangeOptions()
{
	eraseExchangeOptions();

	array<int, 3> typesCount{ 0,0,0 };

	for (list<Card*>::iterator it = this->handCards.begin(); it != this->handCards.end(); ++it) {
		if (*(*it)->getArmyType() == ArmyType::infantry) {
			++typesCount[0];
		}
		else if (*(*it)->getArmyType() == ArmyType::artillery) {
			++typesCount[1];
		}
		else {
			++typesCount[2];
		}
	}

	addExchangeOptionsOfSameCards(typesCount);
	addExchangeOptionsOfDifferentCards(typesCount);
}

// check if we can trad in a set of matched cards
bool Hand::hasExchange() const
{
	if (this->exchangeOptions.size() > 0)
		return true;
	return false;
}
//displays the options of set of 3 cards we can trad in
void Hand::displayExchangeOptions() const
{
	if (this->hasExchange()) {
		cout << "The player has these exchange option(s): " << endl;
		int optionId{ 1 };
		for (auto optionIt = exchangeOptions.begin(); optionIt != exchangeOptions.end(); ++optionIt) {
			cout << "Option #" << optionId << " : ";
			for (size_t t{ 0 }; t < optionIt->size(); ++t) {

				if (t > 0 && t < optionIt->size())
					cout << ", ";

				if (*(*optionIt)[t]->getArmyType() == ArmyType::infantry) {
					cout << "Infantry";
				}
				else if (*(*optionIt)[t]->getArmyType() == ArmyType::artillery) {
					cout << "Artillery";
				}
				else {
					cout << "Cavalry";
				}
			}
			cout << endl;
			++optionId;
		}
	}
	else {
		cout << "The player has no exchange options." << endl;
	}
}
// exchange the a set of 3 cards in Amrys
bool Hand::exchange()
{
	this->displayExchangeOptions();

	size_t optionId;

	cout << "Enter exchange option #: ";
	cin >> optionId;

	if (optionId <= this->exchangeOptions.size()) {
		auto optionIt = this->exchangeOptions.begin();
		for (size_t t{ 1 }; t < optionId; ++t) {
			++optionIt;
		}
		this->gameDeckPtr->exchange(*optionIt);
		for (size_t t{ 0 }; t < optionIt->size(); ++t) {
			this->handCards.remove((*optionIt)[t]);
		}
		this->updateExchangeOptions();
		return true;
	}
	else {
		cout << "(" << optionId << ") is an invalid exchange #";
		return false;
	}
}
// prints the cards in the hand
void Hand::printCards()
{
	for (auto cardIt = this->handCards.begin(); cardIt != this->handCards.end(); ++cardIt) {
		cout << "Card id: " << (*cardIt)->getCardId() << ", Card Type: ";
		if (*(*cardIt)->getArmyType() == ArmyType::artillery)
			cout << "Artillery" << endl;
		else if (*(*cardIt)->getArmyType() == ArmyType::cavalry)
			cout << "Cavalry" << endl;
		else
			cout << "Infantry" << endl;
	}
}
// clear the number of option in the exahngeOptions in order to fill it again with available options
void Hand::eraseExchangeOptions()
{
	//clearing the options
	int t = this->exchangeOptions.size();

	while (t != 0) {
		this->exchangeOptions.erase(this->exchangeOptions.begin());
		t--;
	}
}
//add an option of same type of army cards like 3 cards of infantry cards
void Hand::addExchangeOptionsOfSameCards(const array<int, 3> & typesCount)
{
	for (int t = 0; t <= 2; ++t) {
		if (typesCount[t] >= 3) {
			array<Card*, 3> exchangeOption{ nullptr, nullptr, nullptr };
			auto exchangeOptionIt = this->exchangeOptions.insert(this->exchangeOptions.end(), exchangeOption);//
			int cardInOption = 0;
			auto cardInHand = this->handCards.begin();
			while (cardInOption < 3) {
				if
					(
					(t == 0 && *(*cardInHand)->getArmyType() == ArmyType::infantry) ||
						(t == 1 && *(*cardInHand)->getArmyType() == ArmyType::artillery) ||
						(t == 2 && *(*cardInHand)->getArmyType() == ArmyType::cavalry)) {

					(*exchangeOptionIt)[cardInOption] = *cardInHand;
					++cardInOption;

				}
				++cardInHand;
			}
		}
	}
}
//add an option of different type of army cards like {infantry, artillery , cavalry}
void Hand::addExchangeOptionsOfDifferentCards(const array<int, 3> & typesCount)
{
	if (typesCount[0] > 0 && typesCount[1] > 0 && typesCount[2] > 0) {
		array<Card*, 3> exchangeOption{ nullptr, nullptr, nullptr };
		auto exchangeOptionIt = this->exchangeOptions.insert(this->exchangeOptions.end(), exchangeOption);
		auto cardInHand = this->handCards.begin();
		while ((*exchangeOptionIt)[0] == nullptr || (*exchangeOptionIt)[1] == nullptr || (*exchangeOptionIt)[2] == nullptr) {


			if ((*exchangeOptionIt)[0] == nullptr && *(*cardInHand)->getArmyType() == ArmyType::infantry)
				(*exchangeOptionIt)[0] = *cardInHand;

			if ((*exchangeOptionIt)[1] == nullptr && *(*cardInHand)->getArmyType() == ArmyType::artillery)
				(*exchangeOptionIt)[1] = *cardInHand;

			if ((*exchangeOptionIt)[2] == nullptr && *(*cardInHand)->getArmyType() == ArmyType::cavalry)
				(*exchangeOptionIt)[2] = *cardInHand;

			++cardInHand;
		}
	}
}

int Deck::getNumOfExchanges()
{
	return numOfExchanges;
}

int Hand::getNumberOfExchanges()
{
	return gameDeckPtr->getNumOfExchanges();
}

int Hand::getNumHandCards()
{
	return handCards.size();
}