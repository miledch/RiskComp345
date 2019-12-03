#pragma once
#include <list>

#include <iterator>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Map.h"
#include "Dice.h"
#include "MapLoader.h"
#include "Cards.h"
#include "GameObservers.h"
#include "PlayerStrategies.h"

using namespace std;

class Player : public Subject {
private:
	vector<Continent>* continents;
	vector<Country*>* countries;
	Dice_Rolling_Facility* dice;
	Hand* h;
	Map *map; // player needs visibility to the map
	string* name; // A player needs a name
	int* availableArmies;
	Strategy *strategy;

	vector<string>* viewBuffer; // This can be considered as the 'view' it will store the things it will print
	bool* newPhase; // To indicate if the player has entered a new phase

public:
	Player();
	Player(Strategy* s);
	Player(Map *map, vector<Country*> *c, Dice_Rolling_Facility *d, Hand *h, string *name);
	Player(const Player& p2);
	Player& operator=(const Player& rhs);
	void changeCountries(vector<Country*>* c);
	~Player();
	Dice_Rolling_Facility* getDice();
	Hand* getHand();
	vector<Country*>* getCountries() const;
	string* getName();
	bool* getNewPhase();
	int* getAvailableArmies();
	vector<string>* getViewBuffer();
	Map* getMap();
	Strategy* getStrategy();
	void setAvailableArmies(int armies);
	void changeHand(Hand* c);
	void printCountries();
	void reinforce();
	void attack();
	void attackPhase(bool& keepAttacking);
	void fortify();
	Country* chosingCountrySource();
	vector<Country*> ownedNieghbourCountry(Country& c);
	bool hasOwnedNieghbourCountry(Country& c);
	Country* chooseTargetCountry(vector<Country*> cl);
	Country* getCountryById(int id);
	Country* get(list<Country*> l, int index);
	void movingArmy(Country* source, Country* target);
	int getArmyByExchangingCards();
	void placingArmy(int& rewardedArmy);
	int getArmyByCountriesOwned();
	int getArmyByContinentsOwned();
	void addCountry(Country* c);
	void addContinent(Continent c);
	void initializeHand(Hand&);
	int getNumPlayerCountries();
	int getNumPlayerContienent();
	int getNumMapCountries();
	int getNumMapContienent();
	void setStrategy(Strategy* s);
	void executeStrategy();
	Country* strongestCountry(vector<Country*>&);
	Country* weakestCountry(vector<Country*>&);
	void fortifyToStrongest();
	void fortifyToWeakest();
	bool hasEnemyNeibour(Country& c);
	Strategy* getStrategy();
	void resetPlayer(Map* map);
};

class PlayerDriver 
{
public:
	static void run();
	static void runAttackPhase();
	static void runFortification();
	static void runReinforcement();
};

