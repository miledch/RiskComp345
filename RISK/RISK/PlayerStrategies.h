#pragma once
#include <iostream>

using namespace std;
class Player;
class Strategy {
public:
	virtual void execute(Player *p) = 0;

	//////////////////// REINFORCE DECISIONS ////////////////////

	virtual Country* chooseCountryToReinforce(vector<Country*>* countries) = 0;

	// Returns number of reinforce armies 
	virtual int getReinforceArmy(int rewardedArmy) = 0;

	//////////////////// FORTIFY DECISIONS ////////////////////

	 // Returns which country you want to take armies from
	virtual int getFortifySource(vector<Country*> countries) = 0;

	// Returns which country you want to transfer armies to
	virtual int getFortifyTarget(vector<Country*> countries) = 0;

	// Returns the number of armies that you want to transfer
	virtual int getFortifyArmy(Country* source) = 0;

	//////////////////// ATTACK DECISIONS ////////////////////

	// Returns decision to attack or not
	virtual int getAttackDecision() = 0;
	virtual int getAttackSource(vector<Country*> countries) = 0;
	virtual int getAttackTarget(vector<int> validEntryForAttack) = 0;
	virtual int getAttackDice(int maxDice) = 0;
	virtual int getDefenceDice(int maxDice) = 0;

	// Returns number of armies you want to transfer after defeating a country
	virtual int getTransferArmies(int maxArmies) = 0;

	/* Same as the methods in Player class but we need to use it from a Strategy object*/
	Country* strongestCountry(vector<Country*>& myCountries);
	Country* weakestCountry(vector<Country*>& countries);

	virtual bool isHuman() = 0;
};

class HumanPlayer : public Strategy {
public:
	void execute(Player* p);

	//////////////////// REINFORCE DECISIONS ////////////////////

	Country* chooseCountryToReinforce(vector<Country*>* countries);
	int getReinforceArmy(int rewardedArmy);

	//////////////////// FORTIFY DECISIONS ////////////////////

	int getFortifySource(vector<Country*> countries);
	int getFortifyTarget(vector<Country*> countries);
	int getFortifyArmy(Country* source);

	//////////////////// ATTACK DECISIONS ////////////////////

	int getAttackDecision();
	int getAttackSource(vector<Country*> countries);
	int getAttackTarget(vector<int> validEntryForAttack);
	int getAttackDice(int maxDice);
	int getDefenceDice(int maxDice);
	int getTransferArmies(int maxArmies);

	bool isHuman();
};

class AggressivePlayer : public Strategy {
public:
	void execute(Player* p);

	//////////////////// REINFORCE DECISIONS ////////////////////

	Country* chooseCountryToReinforce(vector<Country*>* countries);
	int getReinforceArmy(int rewardedArmy);

	//////////////////// FORTIFY DECISIONS ////////////////////

	int getFortifySource(vector<Country*> countries);
	int getFortifyTarget(vector<Country*> countries);
	int getFortifyArmy(Country* source);

	//////////////////// ATTACK DECISIONS ////////////////////

	int getAttackDecision();
	int getAttackSource(vector<Country*> countries);
	int getAttackTarget(vector<int> validEntryForAttack);
	int getAttackDice(int maxDice);
	int getDefenceDice(int maxDice);
	int getTransferArmies(int maxArmies);
	bool isHuman();
};

class BenevolentPlayer : public Strategy {
public:
	void execute(Player* p);

	//////////////////// REINFORCE DECISIONS ////////////////////

	Country* chooseCountryToReinforce(vector<Country*>* countries);
	int getReinforceArmy(int rewardedArmy);

	//////////////////// FORTIFY DECISIONS ////////////////////

	int getFortifySource(vector<Country*> countries);
	int getFortifyTarget(vector<Country*> countries);
	int getFortifyArmy(Country* source);

	//////////////////// ATTACK DECISIONS ////////////////////

	int getAttackDecision();
	int getAttackSource(vector<Country*> countries);
	int getAttackTarget(vector<int> validEntryForAttack);
	int getAttackDice(int maxDice);
	int getDefenceDice(int maxDice);
	int getTransferArmies(int maxArmies);
	bool isHuman();
};

class RandomPlayer : public Strategy {
public:
	void execute(Player* p);

	//////////////////// REINFORCE DECISIONS ////////////////////

	Country* chooseCountryToReinforce(vector<Country*>* countries);
	int getReinforceArmy(int rewardedArmy);

	//////////////////// FORTIFY DECISIONS ////////////////////

	int getFortifySource(vector<Country*> countries);
	int getFortifyTarget(vector<Country*> countries);
	int getFortifyArmy(Country* source);

	//////////////////// ATTACK DECISIONS ////////////////////

	int getAttackDecision();
	int getAttackSource(vector<Country*> countries);
	int getAttackTarget(vector<int> validEntryForAttack);
	int getAttackDice(int maxDice);
	int getDefenceDice(int maxDice);
	int getTransferArmies(int maxArmies);
	bool isHuman();
};