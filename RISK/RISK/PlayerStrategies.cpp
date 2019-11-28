#include "Player.h"

//////////////////////////////// HUMANPLAYER //////////////////////////////// 

void HumanPlayer::execute(Player* p) {
	p->reinforce();
	p->attack();
	p->fortify();
}

Country* HumanPlayer::chooseCountryToReinforce(vector<Country*>* countries)
{
	int in;
	while (true) {
		cin >> in;
		if (in >= 1 && in <= countries->size()) {
			return countries->at(in - 1);
		}
		else {
			cout << "Invalid input. Try again." << endl;
		}
	}
}

int HumanPlayer::getReinforceArmy(int rewardedArmy)
{
	int in;
	while (true) {
		cin >> in;
		if (in >= 1 && in <= rewardedArmy) {
			return in;
		}
		else {
			cout << "Invalid input. Try again." << endl;
		}
	}
}

int HumanPlayer::getFortifySource(vector<Country*> countries)
{
	int source;
	cin >> source;
	return source;
}

int HumanPlayer::getFortifyTarget(vector<Country*> countries)
{
	int target;
	cin >> target;
	return target;
}

int HumanPlayer::getFortifyArmy(Country* source)
{
	int army;
	cin >> army;
	return army;
}

int HumanPlayer::getAttackDecision()
{
	int decision;
	cin >> decision;
	return decision;
}

int HumanPlayer::getAttackSource(vector<Country*> countries)
{
	int source;
	cin >> source;
	return source;
}

int HumanPlayer::getAttackTarget(vector<int> validEntryForAttack)
{
	int attackSelection;
	cin >> attackSelection;
	return attackSelection;
}

int HumanPlayer::getAttackDice(int maxDice)
{
	int dice;
	cin >> dice;
	return dice;
}

int HumanPlayer::getDefenceDice(int maxDice)
{
	int dice;
	cin >> dice;
	return dice;
}

int HumanPlayer::getTransferArmies(int maxArmies)
{
	int transfer;
	cin >> transfer;
	return transfer;
}

//////////////////////////////// AGGRESSIVEPLAYER //////////////////////////////// 

void AggressivePlayer::execute(Player* p) {
	p->reinforce();
	p->attack();
	p->fortify();
}

Country* AggressivePlayer::chooseCountryToReinforce(vector<Country*>* countries)
{
	return strongestCountry(*countries);
}

int AggressivePlayer::getReinforceArmy(int rewardedArmy)
{
	return rewardedArmy;
}

int AggressivePlayer::getFortifySource(vector<Country*> countries)
{
	return 1;
}

int AggressivePlayer::getFortifyTarget(vector<Country*> countries)
{
	Country* target = strongestCountry(countries);
	// Find the position of the strongest country in the vector and return that number
	for (int i = 0; i < countries.size(); i++) {
		if ((*target->getCountryName()) == (*countries[i]->getCountryName())) {
			return (i + 1);
		}
	}
}

int AggressivePlayer::getFortifyArmy(Country* source)
{
	return ((*source->getCountryNumberArmies()) - 1);
}

int AggressivePlayer::getAttackDecision()
{
	return 1;
}

int AggressivePlayer::getAttackSource(vector<Country*> countries)
{
	int source = *strongestCountry(countries)->getCountryID();
	return source;
}

int AggressivePlayer::getAttackTarget(vector<int> validEntryForAttack)
{
	int attackSelection;
	int index = (rand() % validEntryForAttack.size());
	attackSelection = validEntryForAttack[index];
	return attackSelection;
}

int AggressivePlayer::getAttackDice(int maxDice)
{
	return maxDice;
}

int AggressivePlayer::getDefenceDice(int maxDice)
{
	return maxDice;
}

int AggressivePlayer::getTransferArmies(int maxArmies)
{
	return (maxArmies/2);
}

//////////////////////////////// BENEVOLENTPLAYER //////////////////////////////// 

void BenevolentPlayer::execute(Player* p) {
	p->reinforce();
	p->fortify();
}

Country* BenevolentPlayer::chooseCountryToReinforce(vector<Country*>* countries)
{
	return weakestCountry(*countries);
}

int BenevolentPlayer::getReinforceArmy(int rewardedArmy)
{
	return 1;
}

int BenevolentPlayer::getFortifySource(vector<Country*> countries)
{
	Country* source = strongestCountry(countries);
	// Find the position of the strongest country in the vector and return that number
	for (int i = 0; i < countries.size(); i++) {
		if ((*source->getCountryName()) == (*countries[i]->getCountryName())) {
			return (i + 1);
		}
	}
}

int BenevolentPlayer::getFortifyTarget(vector<Country*> countries)
{
	Country* target = weakestCountry(countries);
	// Find the position of the weakest country in the vector and return that number
	for (int i = 0; i < countries.size(); i++) {
		if ((*target->getCountryName()) == (*countries[i]->getCountryName())) {
			return (i + 1);
		}
	}
}

int BenevolentPlayer::getFortifyArmy(Country* source)
{
	return 1;
}

int BenevolentPlayer::getAttackDecision()
{
	return 2;
}

int BenevolentPlayer::getAttackSource(vector<Country*> countries)
{
	return 0;
}

int BenevolentPlayer::getAttackTarget(vector<int> validEntryForAttack)
{
	return 0;
}

int BenevolentPlayer::getAttackDice(int maxDice)
{
	return 1;
}

int BenevolentPlayer::getDefenceDice(int maxDice)
{
	return 1;
}

int BenevolentPlayer::getTransferArmies(int maxArmies)
{
	return 1;
}

//////////////////////////////// MISCELLANEOUS //////////////////////////////// 

Country* Strategy::strongestCountry(vector<Country*>& myCountries)
{
	Country* strong = nullptr;
	int i = 0;
	vector<Country*>::iterator it = myCountries.begin();
	for (; it != myCountries.end(); it++) {
		if (i == 0) {
			strong = (*it);
			i++;
		}
		if (*(*it)->getCountryNumberArmies() > * (strong->getCountryNumberArmies()))
			strong = (*it);
	}
	return strong;
}

Country* Strategy::weakestCountry(vector<Country*>& countries)
{
	Country* weak = nullptr;
	int i = 0;
	vector<Country*>::iterator it = countries.begin();
	for (; it != countries.end(); it++) {
		if (i == 0) {
			weak = (*it);
			i++;
		}
		if (*(*it)->getCountryNumberArmies() < *(weak->getCountryNumberArmies()))
			weak = (*it);
	}
	return weak;
}
