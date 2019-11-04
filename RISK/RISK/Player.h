#pragma once
#include <list>
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Map.h"
#include "Dice.h"
#include "MapLoader.h"
#include "Cards.h"

using namespace std;

class Player {
private:
	vector<Continent>* continents;
	vector<Country*>* countries; // Vector contains pointer to countries so that players
								 // don't contain copies of Country objects from the map but point to the countries themselves
	Dice_Rolling_Facility* dice;
	Hand* h;
	Map *map; // player needs visibility to the map
	string* name; // A player needs a name
	int* availableArmies;

	vector<Continent>* continents{ &testContinents };
	vector<Country>* countries{ &testCounties };
	Dice_Rolling_Facility* dice;
	Hand*  h;
	

public:
	Player();
	//Player(vector<Country*>* c, Dice_Rolling_Facility* d, Hand* h);
	Player(Map *map, vector<Country*> *c, Dice_Rolling_Facility *d, Hand *h, string *name);
	Player(const Player& p2);
	Player& operator=(const Player& rhs);
	void changeCountries(vector<Country*>* c);
	~Player();
	Dice_Rolling_Facility* getDice();
	Hand* getHand();
	void initializeHand(Hand*);
	vector<Country*>* getCountries() const;
	string* getName();
	int* getAvailableArmies();
	void setAvailableArmies(int armies);
	void changeHand(Hand* c);
	void printCountries();
	void reinforce();
	int getArmyByCountriesOwned();
	int getArmyBycontienetOwned();
	int getArmyByExchangingCards();
	void placingArmy(int&);
	void attack();
	void fortify();
	Country& chosingCountrySource();
	list<Country*> ownedNieghbourCountry(Country& c);
	bool hasOwnedNieghbourCountry(Country& c);
	Country* chooseTargetCountry(list<Country*> cl);
	Country* getCountryById(int id);
	Country* get(list<Country*> cl, int id);
	void movingArmy(Country* c1, Country* c2);
	void addCountry(Country* c);
	void addContinent(Continent c);

};

class PlayerDriver 
{
public:
	static void run();
	static void runReinforcement();
	static void runFortification();
};

