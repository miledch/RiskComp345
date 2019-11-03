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
	vector<Country>* countries;
	Dice_Rolling_Facility* dice;
	Hand* h;


public:
	Player();
	Player(vector<Country>* c, Dice_Rolling_Facility* d, Hand* g);//collection of coutries, dice, and hands are properties of a player. they must be initialized inside the player object, instead
	//of passing them as parameters. the player object should expect to recieve a map or a game engine that has a deck.
	Player(const Player& p2);
	Player& operator=(const Player& rhs);
	void changeCountries(vector<Country>* c);
	~Player();
	Dice_Rolling_Facility* getDice();
	Hand* getHand();
	vector<Country>* getCountries();
	void changeHand(Hand* c);
	void printCountries();
	void reinforce();
	int getArmyByCountriesOwned();
	int getArmyByContinentsOwned();
	int getArmyByExchangingCards();
	void placingArmy(int& id);
	void attack();
	void fortify();
	Country& chosingCountrySource();
	list<Country*> ownedNieghbourCountry(Country& c);
	bool hasOwnedNieghbourCountry(Country& c);
	Country* chooseTargetCountry(list<Country*> cl);
	Country* getCountryById(int id);
	Country* get(list<Country*> cl, int id);
	void movingArmy(Country* c1, Country* c2);
	void addCountry(Country c);
	void addContinent(Continent c);

};

class PlayerDriver
{
public:
	static void run();
	static void runReinforcement();
	static void runFortification();
};
