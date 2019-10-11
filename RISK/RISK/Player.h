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
	hand* h;

public:
	Player();
	Player(vector<Country>* c, Dice_Rolling_Facility* d, hand* g);
	void addCountries();
	~Player();
	//void changeCountries();
	Dice_Rolling_Facility* getDice();
	void printCountries();
	void reinforce();
	void attack();
	void fortify();
	static void run();
};

