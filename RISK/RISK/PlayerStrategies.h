#pragma once
#include <iostream>

using namespace std;
class Player;
class Strategy {
public:
	virtual void execute(Player *p) = 0;
	virtual Country* chooseCountryToReinforce(vector<Country*>* countries) = 0;
	virtual int getReinforceArmy(int rewardedArmy) = 0;
	virtual int getFortifySource(vector<Country*> countries) = 0;
	virtual int getFortifyTarget(vector<Country*> countries) = 0;
	virtual int getFortifyArmy(Country* source) = 0;
	virtual int getAttackDecision() = 0;
	virtual int getAttackSource(vector<Country*> countries) = 0;
	virtual int getAttackTarget(vector<int> validEntryForAttack) = 0;
	virtual int getAttackDice(int maxDice) = 0;
	virtual int getDefenceDice(int maxDice) = 0;
	virtual int getTransferArmies(int maxArmies) = 0;

	// Same as the methods in Player class but we need to use it from a Strategy object
	Country* strongestCountry(vector<Country*>& myCountries);
	Country* weakestCountry(vector<Country*>& countries);
};

class HumanPlayer : public Strategy {
public:
	void execute(Player* p);
	Country* chooseCountryToReinforce(vector<Country*>* countries);
	int getReinforceArmy(int rewardedArmy);
	int getFortifySource(vector<Country*> countries);
	int getFortifyTarget(vector<Country*> countries);
	int getFortifyArmy(Country* source);
	int getAttackDecision();
	int getAttackSource(vector<Country*> countries);
	int getAttackTarget(vector<int> validEntryForAttack);
	int getAttackDice(int maxDice);
	int getDefenceDice(int maxDice);
	int getTransferArmies(int maxArmies);
};

class AggressivePlayer : public Strategy {
public:
	void execute(Player* p);
	Country* chooseCountryToReinforce(vector<Country*>* countries);
	int getReinforceArmy(int rewardedArmy);
	int getFortifySource(vector<Country*> countries);
	int getFortifyTarget(vector<Country*> countries);
	int getFortifyArmy(Country* source);
	int getAttackDecision();
	int getAttackSource(vector<Country*> countries);
	int getAttackTarget(vector<int> validEntryForAttack);
	int getAttackDice(int maxDice);
	int getDefenceDice(int maxDice);
	int getTransferArmies(int maxArmies);
};

class BenevolentPlayer : public Strategy {
public:
	void execute(Player* p);
	Country* chooseCountryToReinforce(vector<Country*>* countries);
	int getReinforceArmy(int rewardedArmy);
	int getFortifySource(vector<Country*> countries);
	int getFortifyTarget(vector<Country*> countries);
	int getFortifyArmy(Country* source);
	int getAttackDecision();
	int getAttackSource(vector<Country*> countries);
	int getAttackTarget(vector<int> validEntryForAttack);
	int getAttackDice(int maxDice);
	int getDefenceDice(int maxDice);
	int getTransferArmies(int maxArmies);
};