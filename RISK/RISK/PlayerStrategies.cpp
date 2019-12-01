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

int HumanPlayer::getReinforceArmy(int rewardedArmy, Player& player)
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

int HumanPlayer::getFortifyDecision(Player& player)
{
	int decision;
	cin >> decision;
	return decision;
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
	return strongestCountry(*countries); // Reinforce the strongest country
}

int AggressivePlayer::getReinforceArmy(int rewardedArmy, Player& player)
{
	return rewardedArmy; // Reinforce the strongest army with all armies at once
}

int AggressivePlayer::getFortifyDecision(Player& player)
{
	return 1;
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
	return 1; // Always attack if possible
}

int AggressivePlayer::getAttackSource(vector<Country*> countries)
{
	int source = *strongestCountry(countries)->getCountryID();
	return source; // Always attack from strongest country
}

int AggressivePlayer::getAttackTarget(vector<int> validEntryForAttack)
{
	int attackSelection;
	int index = (rand() % validEntryForAttack.size());
	attackSelection = validEntryForAttack[index];
	return attackSelection; // Attack a random country
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
	return weakestCountry(*countries); // Always reinforce the weaker countries
}

int BenevolentPlayer::getReinforceArmy(int rewardedArmy, Player& player)
{
	return 1; // Don't use all the armies, instead reinforce the weak countries 1 by 1
}

int BenevolentPlayer::getFortifyDecision(Player& player)
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

// Attack decisions for benevolent CPU don't matter since it won't ever attack anyway
int BenevolentPlayer::getAttackDecision()
{
	return 2; // Never attack
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

//////////////////////////////// RANDOMPLAYER //////////////////////////////// 

void RandomPlayer::execute(Player* p)
{
}

// All decisions for RandomPlayer CPU are chosen randomly
Country* RandomPlayer::chooseCountryToReinforce(vector<Country*>* countries)
{
	int index = rand() % countries->size();
	return (*countries)[index];
}

int RandomPlayer::getReinforceArmy(int rewardedArmy, Player& player)
{
	return ((rand() % rewardedArmy) + 1);
}

int RandomPlayer::getFortifyDecision(Player& player)
{
	return 1;
}

int RandomPlayer::getFortifySource(vector<Country*> countries)
{
	int index = rand() % countries.size();
	return (index+1);
}

int RandomPlayer::getFortifyTarget(vector<Country*> countries)
{
	int index = rand() % countries.size();
	return (index + 1);
}

int RandomPlayer::getFortifyArmy(Country* source)
{
	int army = rand() % (*source->getCountryNumberArmies());
	return 0;
}

int RandomPlayer::getAttackDecision()
{
	int decision = (rand() % 2) + 1;
	return decision;
}

int RandomPlayer::getAttackSource(vector<Country*> countries)
{
	int index = (rand() % countries.size());
	int id = (*countries[index]->getCountryID());
	return id;
}

int RandomPlayer::getAttackTarget(vector<int> validEntryForAttack)
{
	int attackSelection;
	int index = (rand() % validEntryForAttack.size());
	attackSelection = validEntryForAttack[index];
	return attackSelection;
}

int RandomPlayer::getAttackDice(int maxDice)
{
	int dice = (rand() % maxDice) + 1;
	return dice;
}

int RandomPlayer::getDefenceDice(int maxDice)
{
	int dice = (rand() % maxDice) + 1;
	return dice;
}

int RandomPlayer::getTransferArmies(int maxArmies)
{
	int transfer = (rand() % maxArmies) + 1;
	return transfer;
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

//////////////////////////////// CHEATERPLAYER //////////////////////////////// 

void CheaterPlayer::execute(Player* p)
{
}

Country* CheaterPlayer::chooseCountryToReinforce(vector<Country*>* countries)
{
	return strongestCountry(*countries);
}

int CheaterPlayer::getReinforceArmy(int rewardedArmy, Player& player)
{
	Country* strongestCountry = this->strongestCountry(*player.getCountries());
	for (int i = 0; i < player.getNumPlayerCountries(); i++) {
		*(*player.getCountries())[i]->getCountryNumberArmies() *= 2;
	}// Double the armies in each country

	cout << "** Cheater CPU player has doubled its armies on every country!**" << endl;

	// Remove 'rewarded' # of armies from the strongest country because it will 
	//be added later again from the placingArmy() method since we return 
	//rewardedArmy from this function
	*strongestCountry->getCountryNumberArmies() -= rewardedArmy;

	return rewardedArmy;
}

int CheaterPlayer::getFortifyDecision(Player& player)
{
	// Get all the countries from the map
	list<Country> mapCountries = *(player.getMap()->getCountries());
	list<Country>::iterator countriesIt;

	// Get the player's countries
	vector<Country*> myCountries = *(player.getCountries());
	vector<Country*>::iterator myCountryIt;

	// Get all the neighbors of all the player's countries
	list<int> neighbors;
	list<int>::iterator neighborId;

	// Iterate through the vector of countries for that player
	for (myCountryIt = myCountries.begin(); myCountryIt != myCountries.end(); ++myCountryIt) {
		neighbors = *((*myCountryIt)->getNeighbors());
		// Iterate through the list of neighbors of each country of that player
		for (neighborId = neighbors.begin(); neighborId != neighbors.end(); ++neighborId) {
			for (countriesIt = mapCountries.begin(); countriesIt != mapCountries.end(); ++countriesIt) {
				if (*countriesIt->getCountryID() == *neighborId) {
					// If the neighboring country belongs to an enemy
					if (*countriesIt->getCountryPlayerOwned() != *player.getName()) {
						*((*myCountryIt)->getCountryNumberArmies()) *= 2; // Double the number of armies
						cout << "Cheater CPU has doubled the number of armies in: " << *(*myCountryIt)->getCountryName() << "!" << endl;
					}
					break;
				}
			}
		}
	}

	return 2; // 2 for 'no' decision
}
