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

using namespace std;

class Player {
private:
	vector<Country>* countries;
	Dice_Rolling_Facility* dice;
	Hand* h;

	string* name;

public:
	Player();
	Player(vector<Country>* c, Dice_Rolling_Facility* d, Hand* h);
	Player(vector<Country>* c, Dice_Rolling_Facility* d, Hand* h, string* name);
	Player(const Player& p2);
	Player& operator=(const Player& rhs);
	void changeCountries(vector<Country>* c);
	~Player();
	Dice_Rolling_Facility* getDice();
	Hand* getHand();
	vector<Country>* getCountries();
	string* getName();
	void changeHand(Hand* c);
	void printCountries();
	void reinforce();
	void attack();
	void fortify();
	static void run();
};

class PlayerDriver 
{
public:
	static void run();
};

