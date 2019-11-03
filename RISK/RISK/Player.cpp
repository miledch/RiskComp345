#include "Player.h"

// Default constructor
Player::Player()
{
	map = new Map();
	countries = new vector<Country>();
	dice = new Dice_Rolling_Facility();
	h = new Hand(*(new Deck(0)));
	name = new string("DefaultPlayer");
	availableArmies = new int(0);
}

// Parameterized constructor
Player::Player(vector<Country>* c, Dice_Rolling_Facility* d, Hand* h)
{
	this->countries = c;
	this->dice = d;
	this->h = h;
	this->name = new string("DefaultPlayer");
	this->availableArmies = new int(0);
	map = nullptr;
}

Player::Player(Map* map, vector<Country>* c, Dice_Rolling_Facility* d, Hand* h, string* name)
{
	this->map = map;
	this->countries = c;
	this->dice = d;
	this->h = h;
	this->name = name;
	this->availableArmies = new int(0);
}

Player::Player(const Player& p2)
{
	this->map = new Map(*p2.map);
	this->countries = new vector<Country>(*p2.countries);
	this->dice = new Dice_Rolling_Facility(*p2.dice);
	this->h = new Hand(*p2.h);
	this->name = new string(*p2.name);
	this->availableArmies = new int(*p2.availableArmies);
}

Player& Player::operator=(const Player& rhs)
{
	if (this != &rhs) 
	{
		*(this->map) = *(rhs.map);
		*(this->countries) = *(rhs.countries);
		*(this->dice) = *(rhs.dice);
		*(this->h) = *(rhs.h);
		*(this->name) = *(rhs.name);
		*(this->availableArmies) = *(rhs.availableArmies);
	}
	return *this;
}

// Destructor
Player::~Player()
{
	for (vector<Country>::iterator it = countries->begin(); it != countries->end(); ++it)
	{
		it->deleteCountry();
	}
	//delete map;
	//map = NULL;
	//delete h;
	//h = NULL;
	delete dice;
	dice =NULL;
	delete name;
	name = NULL;
	delete availableArmies;
	availableArmies = NULL;

}

// Get player's dice
Dice_Rolling_Facility* Player::getDice()
{
	return this->dice;
}

// Get player's hand of cards
Hand* Player::getHand()
{
	return this->h;
}

// Get player's vector of countries
vector<Country>* Player::getCountries() const
{
	return this->countries;
}

string* Player::getName()
{
	return name;
}

int* Player::getAvailableArmies()
{
	return availableArmies;
}

void Player::setAvailableArmies(int armies)
{
	*(this->availableArmies) = armies;
}

// Change the set of player's countries
void Player::changeCountries(vector<Country>* c)
{
	this->countries = c;
}

// Change the hand of cards
void Player::changeHand(Hand* hd)
{
	this->h = hd;
}

// Print player's countries
void Player::printCountries()
{
	if (countries->empty() == true)
	{
		cout << "This player has no countries!\n";
	}
	else
	{
		for (unsigned int i = 0; i < countries->size(); i++) {
			Country c = countries->at(i);
			cout << c.getCountryName() << endl;
		}
		// for (int i = 0; i < countries->size(); i++) 
		// {
		// 	Country c = countries->at(i);
		// 	c.printCountry();
		// 	cout << endl;
		// }
	}
}

void Player::reinforce()
{
	cout << "I'm reinforcing!\n";
	int availableArmies{ 0 };
	availableArmies = getArmyByCountriesOwned() + getArmyByContinentsOwned() + getArmyByExchangingCards();
	cout << "Total # of arnies rewarded is " << availableArmies << "." << endl;
	placingArmy(availableArmies);
}

void Player::attack()
{
	int playerDecision = 0;
	while (playerDecision != 2)
	{
		cout << "\nDo you want to attack adjacent territories ?" << endl;
		cout << "Press 1 for yes or 2 for no: ";
		cout << ">";
		cin >> playerDecision;
		if (playerDecision == 1)
			attackPhase();
	}
}

void Player::attackPhase()
{
	Country* attackCountry = NULL;
	Country* targetedCountry = NULL;

	int countrySelected;
	bool validSelection = false;
	vector<Country>::iterator it;
	//The player selects one of its countries to attack from, The attacking country must have at least 2 armies on it
	do
	{
		cout << "\nSelect which countries you want to attack from by entering the country ID" << endl << endl;

		for (it = countries->begin(); it != countries->end(); ++it)
		{
			if (*(it->getCountryNumberArmies()) >= 2)
			{
				cout << *it->getCountryID() << "\tCountry " << *it->getCountryName() << " has " << *it->getCountryNumberArmies() << " armies available" << endl;
			}
		}
		cout << ">";
		cin >> countrySelected;
		for (it = countries->begin(); it != countries->end(); ++it)
		{
			if (*it->getCountryNumberArmies() >= 2)
			{
				if (countrySelected == *it->getCountryID())
				{
					attackCountry = &(*it);
					validSelection = true;
				}
					
			}
		}
		if(!validSelection)
			cout << "Enter a valid country ID " << endl;
	} 
	while (!validSelection);

	//find the index of the countries list corresponding to our countrySelected;
	int index;
	for (it = countries->begin(); it != countries->end(); ++it)
	{
		if (*it->getCountryID() == countrySelected)
		{
			index = std::distance(countries->begin(), it);
			break;
		}
	}

	cout << "\nChoose a country to attack !" << endl;
	cout << "Neighboring countries of country " << countrySelected << " are:" << endl << endl;

	list<int>::iterator l_it;
	list<Country>::iterator countriesIt;
	vector<int> validEntryForAttack;
	for (l_it = attackCountry->getNeighbors()->begin(); l_it != attackCountry->getNeighbors()->end(); ++l_it)
	{
		for (countriesIt = map->getCountries()->begin(); countriesIt != map->getCountries()->end(); ++countriesIt)
		{
			if (*countriesIt->getCountryID() == *l_it)
			{
				cout << *countriesIt->getCountryID() << "\t" << *countriesIt->getCountryName() << " containing " << *countriesIt->getCountryNumberArmies() << " armies." << endl;
				validEntryForAttack.push_back(*countriesIt->getCountryID());
				break;
			}
		}
	}
	int attackSelection;
	validSelection = false;
	vector<int>::iterator vecInt_it;
	do
	{
		cout << ">";
		cin >> attackSelection;
		for (vecInt_it = validEntryForAttack.begin(); vecInt_it != validEntryForAttack.end(); vecInt_it++)
		{
			if (attackSelection == *vecInt_it)
			{
				validSelection = true;
			}
				
		}
		if (!validSelection)
		{
			cout << "Please enter a valid country ID" << endl;
			for (l_it = attackCountry->getNeighbors()->begin(); l_it != attackCountry->getNeighbors()->end(); ++l_it)
			{
				for (countriesIt = map->getCountries()->begin(); countriesIt != map->getCountries()->end(); ++countriesIt)
				{
					if (*countriesIt->getCountryID() == *l_it)
					{
						cout << *countriesIt->getCountryID() << "\t" << *countriesIt->getCountryName() << " containing " << *countriesIt->getCountryNumberArmies() << " armies." << endl;
						break;
					}
				}
			}
		}	
	} 
	while (!validSelection);

	// assign the pointer to the target country
	for (countriesIt = map->getCountries()->begin(); countriesIt != map->getCountries()->end(); ++countriesIt)
	{
		if (*countriesIt->getCountryID() == attackSelection)
		{
			targetedCountry = &(*countriesIt);
		}
	}

	// The attacker is allowed 1 to 3 dice, with the maximum number of dice being the number of armies on the attacking country, minus one.
	cout << "\nAttacker country " << *countries->at(index).getCountryID() << " " << *countries->at(index).getCountryName() <<
		" is owned by " << *countries->at(index).getCountryPlayerOwned() << endl;
	cout << "Please select your number of dice to roll for your attack!" << endl;
	int attackerNbrDice;
	validSelection = false;
	do
	{
		// for loop to display the dice options
		int maxDice;
		switch (*attackCountry->getCountryNumberArmies())
		{
		case 3:
			maxDice = 2;
			break;
		case 2:
			maxDice = 1;
			break;
		default:
			maxDice = 3;
			break;
		}
		for (size_t i = 1; i <= maxDice; i++)
		{
			cout << i << ": " << i << " dice" << endl;
		}
		cout << ">";
		cin >> attackerNbrDice;
		// for loop to check if the dice input is a valid selection
		for (size_t i = 1; i <= maxDice; i++)
		{
			if (attackerNbrDice == i)
			{
				validSelection = true;
				break;
			}	
		}
		if(!validSelection)
			cout << "Please enter a valid dice number" << endl;
	} 
	while (!validSelection);

	
	// The defender is allowed 1 to 2 dice, with the maximum number of dice being the number of armies on the defending country
	// if the defending country has 1 army, only 1 dice allowed. For 2 armies and +, then he is allowed 2 dice
	int defenderNbrDice;

	cout << "\nDefender country " << *targetedCountry->getCountryID() << " " << *targetedCountry->getCountryName() <<
		" is owned by " << *targetedCountry->getCountryPlayerOwned() << endl;
	if (*targetedCountry->getCountryNumberArmies() == 0)
	{
		cerr << "***This country has no armies***" << endl;
		cerr << "This is an error, not supposed to print this message";
		return;
	}
				
	cout << "Please select your number of dice to roll for your defense!" << endl;
	validSelection = false;
	do
	{
		// for loop to display the dice options
		int maxDice;
		switch (*targetedCountry->getCountryNumberArmies())
		{
		case 1:
			maxDice = 1;
			break;
		default:
			maxDice = 2;
			break;
		}
		for (size_t i = 1; i <= maxDice; i++)
		{
			cout << i << ": " << i << " dice" << endl;
		}
		cout << ">";
		cin >> defenderNbrDice;
		// for loop to check if the dice input is a valid selection
		for (size_t i = 1; i <= maxDice; i++)
		{
			if (defenderNbrDice == i)
			{
				validSelection = true;
				break;
			}
		}
		if (!validSelection)
			cout << "Please enter a valid dice number" << endl;
	} 
	while (!validSelection);


	// Attacker rolls his dices
	vector<int> attackerRoll = this->getDice()->roll(attackerNbrDice);
	// Defender rolls his dices
	vector<int> defenderRoll = this->getDice()->roll(defenderNbrDice);
	cout << endl;
	cout << *attackCountry->getCountryPlayerOwned() << " country " << *attackCountry->getCountryID()
		<< " " << *attackCountry->getCountryName() << " rolled ";
	for (vecInt_it = attackerRoll.begin(); vecInt_it != attackerRoll.end(); vecInt_it++)
	{
		cout << *vecInt_it << " ";
	}

	cout << "\n" << *targetedCountry->getCountryPlayerOwned() << " country " << *targetedCountry->getCountryID()
		<< " " << *targetedCountry->getCountryName() << " rolled ";
	for (vecInt_it = defenderRoll.begin(); vecInt_it != defenderRoll.end(); vecInt_it++)
	{
		cout << *vecInt_it << " ";
	}
	cout << endl;

	//Match up the highest attack die with the highest defender die, and match the second highest attack die with the second
	//highest defender die. If there is only one attack die, only match up the highest attack die with the defender die
	const int loopNbr = std::min(attackerNbrDice, defenderNbrDice);
	for (size_t i = 0; i < loopNbr; i++)
	{
		// because attackerRoll is in ascending order, the back() returns the highest roll
		int attack = attackerRoll.back();
		attackerRoll.pop_back();

		int defense = defenderRoll.back();
		if(defenderRoll.size() > 1)
			defenderRoll.pop_back();

		cout << "\nBecause " << *attackCountry->getCountryPlayerOwned() << " rolled " << attack << " and "
			<< *targetedCountry->getCountryPlayerOwned() << " rolled " << defense << endl;
		//Remove one of your opponent�s army from the defending territory if the attack die is higher to its corresponding defense die.
		if (attack > defense)
		{
			targetedCountry->setCountryNumberArmies(--(*targetedCountry->getCountryNumberArmies()));
			cout << "Country " << *targetedCountry->getCountryName() << " from " << *targetedCountry->getCountryPlayerOwned()
				<< " lost one army and is now at " << *targetedCountry->getCountryNumberArmies() << endl;
		}
		else // if dices are equal or defense > attack
		{
			attackCountry->setCountryNumberArmies(--(*attackCountry->getCountryNumberArmies()));
			cout << "Country " << *attackCountry->getCountryName() << " from " << *attackCountry->getCountryPlayerOwned()
				<< " lost one army and is now at " << *attackCountry->getCountryNumberArmies() << endl;
		}

		// check if the attack country ran out of armies
		if (*attackCountry->getCountryNumberArmies() == 0)
		{
			cout << "The aggressor " << *attackCountry->getCountryPlayerOwned() << " has been defeated and lost country "
				<< *attackCountry->getCountryName() << endl;
			// player removes his attack country from his list of countries using our index
			countries->erase(countries->begin() + index);
			// remove this country from the map
			for (countriesIt = map->getCountries()->begin(); countriesIt != map->getCountries()->end(); ++countriesIt)
			{
				if (*countriesIt->getCountryID() == *attackCountry->getCountryID())
				{
					countriesIt->setCountryPlayerOwned("NULL");
					countriesIt->setCountryNumberArmies(0);
					break;
				}
			}
		}
		else if (*targetedCountry->getCountryNumberArmies() == 0)
		{
			cout << "Targeted  " << *targetedCountry->getCountryPlayerOwned() << " has been defeated and lost country "
				<< *targetedCountry->getCountryName() << endl;
			// player now owns the targeted countries
			countries->push_back(*targetedCountry);
			// modify the map object
			for (countriesIt = map->getCountries()->begin(); countriesIt != map->getCountries()->end(); ++countriesIt)
			{
				if (*countriesIt->getCountryID() == attackSelection)
				{
					countriesIt->setCountryPlayerOwned(*attackCountry->getCountryPlayerOwned());
					// player must now decide how many armies to move to the new country
					int nbrArmies;
					validSelection = false;
					do
					{
						cout << "\nIn order to move armies to the conquered country, select a number between 1 and "
							<< (*attackCountry->getCountryNumberArmies() - 1) << endl;
						cout << ">";
						cin >> nbrArmies;
						if (nbrArmies > 1 && nbrArmies < *attackCountry->getCountryNumberArmies())
							validSelection = true;
						else
							cout << "\nPlease enter a valid number" << endl;
					} 
					while (!validSelection);

					countriesIt->setCountryNumberArmies(nbrArmies);
					break;
				}
			}
		}
	}

	attackCountry = nullptr;
	targetedCountry = nullptr;


}

void Player::fortify()
{
	cout << "I'm fortifying!\n";
	Country* source = &(chosingCountrySource());
	list<Country*> possibleTargets = ownedNieghbourCountry(*source);
	Country* target = chooseTargetCountry(possibleTargets);
	movingArmy(source, target);
}

Country& Player::chosingCountrySource()
{
	bool t = true;
	vector<Country*> possibleSource;
	cout << "Please select the country number you want to take troops from :" << endl;
	do {
		int i = 0;
		for (vector<Country>::iterator it = countries->begin(); it != countries->end(); ++it) {
			if (*(it->getCountryNumberArmies()) > 1 || hasOwnedNieghbourCountry(*it)) {
				Country* ptrCountry = &*it;
				possibleSource.push_back(ptrCountry);
				cout << ++i << ". " << *(it->getCountryName()) << " with " << *(it->getCountryNumberArmies()) << "  troops." << endl;
			}
		}
		int in;
		cin >> in;
		if (in > 0 && in < possibleSource.size()) {
			t = false;
			return *(possibleSource.at(in - 1));
		}
		else
			cout << "invalid input.\n" << "try again:" << endl;
	} while (t);
}

list<Country*> Player::ownedNieghbourCountry(Country& source)
{
	list<int>* neighboursID = source.getNeighbors();
	list<int>* myCountriesIds = new list<int>;
	for (vector<Country>::iterator it = countries->begin(); it != countries->end(); it++)
	{
		myCountriesIds->push_back(*it->getCountryID());
	}
	neighboursID->sort();
	myCountriesIds->sort();
	list<int> out;
	set_intersection(neighboursID->begin(), neighboursID->end(), myCountriesIds->begin(), myCountriesIds->end(), back_inserter(out));
	list<Country*> myNeighboursPtr;
	for (list<int>::iterator it = out.begin(); it != out.end(); it++) {
		Country* CountryPtr = getCountryById(*it);
		myNeighboursPtr.push_back(CountryPtr);
	}
	return myNeighboursPtr;
}

bool Player::hasOwnedNieghbourCountry(Country& c)
{
	list<Country*> ownedNieghbour = ownedNieghbourCountry(c);
	return (ownedNieghbour.size() > 0);
}
Country* Player::chooseTargetCountry(list<Country*> targets)
{
	bool t = true;
	cout << "Please select the country number you want to move troops to :" << endl;
	do {
		int i = 0;
		for (list<Country*>::iterator it = targets.begin(); it != targets.end(); ++it) {
			cout << ++i << ". " << (*it)->getCountryName() << " with " << (*it)->getCountryNumberArmies() << "  troops." << endl;
		}
		int in;
		cin >> in;
		if (in > 0 && in < targets.size()) {
			t = false;
			return get(targets, (in - 1));
		}
		else
			cout << "invalid input.\n" << "try again:" << endl;
	} while (t);
}

Country* Player::getCountryById(int id)
{
	vector<Country>::iterator it;
	for (it = countries->begin(); it != countries->end(); it++) {
		if (id == *it->getCountryID()) {
			break;
		}
	}
	Country* c = &*it;
	return c;
}

Country* Player::get(list<Country*> l, int index)
{
	list<Country*>::iterator it = l.begin();
	for (int i = 0; i < index; i++) {
		++it;
	}
	return getCountryById(*(*it)->getCountryID());
}

void Player::movingArmy(Country* source, Country* target)
{
	cout << "you have " << source->getCountryNumberArmies() << "in" << source->getCountryName() << ".\n";
	cout << "you have " << target->getCountryNumberArmies() << "in" << target->getCountryName() << ".\n";
	cout << "how many you want to move from " << source->getCountryName() << " to " << target->getCountryName() << " ." << endl;
	int in;
	cin >> in;
	if (in >= 0 && in < (*source->getCountryNumberArmies() - 1)) {
		source->decreaseArmy(in);
		target->increaseArmy(in);
	}
	cout << "Now you have " << source->getCountryNumberArmies() << "in" << source->getCountryName() << ".\n";
	cout << "and you have " << target->getCountryNumberArmies() << "in" << target->getCountryName() << ".\n";
}


int Player::getArmyByExchangingCards()
{
	int rewardedArmies{ 0 };
	bool doExchange{ false };
	char exchnageOption = 'n';

	if (h->getNumHandCards() == 5) {
		cout << "you have 5 cards. you must exchange some of your cards.\n";
		doExchange = true;
	}
	else if (h->hasExchange()) {
		cout << "Would you like to do an exchange? ('y' for yes, 'n' for no)\n";
		cin >> exchnageOption;
		if (exchnageOption == 'y')
			doExchange = true;
	}

	while (doExchange) {
		if (h->exchange()) {
			doExchange = false;
			rewardedArmies = h->getNumberOfExchanges() * 5;
		}
		else {
			if (h->getNumHandCards() == 5)
				doExchange = true;

			else if (h->hasExchange()) {
				cout << "Would you like to do an exchange? ('y' for yes, 'n' for no)\n";
				cin >> exchnageOption;
				if (exchnageOption == 'y')
					doExchange = true;
			}
			else {
				doExchange = false;
			}
		}
	}
	return rewardedArmies;
}

void Player::placingArmy(int& rewardedArmy)
{
	cout << "Placing the Army...." << endl;
	while (rewardedArmy != 0)
	{
		Country chosenCountry;
		cout << "you have " << rewardedArmy << "to place." << endl;
		cout << "Please select the country number you want to reinfore:" << endl;
		for (vector<Country>::iterator it = countries->begin(); it != countries->end(); ++it) {
			int i = std::distance(countries->begin(), it);
			cout << i << ". " << it->getCountryName() << " with " << it->getCountryNumberArmies() << "  troops." << endl;
		}
		unsigned int in;
		cin >> in;
		if (in >= 1 && in <= countries->size()) {
			chosenCountry = countries->at(in);
		}
		else {
			cout << "invalid input." << endl;
		}
		cout << "choose number of army to place in " << chosenCountry.getCountryName() << "." << endl;
		cin >> in;
		if (in >= 1 && in <= rewardedArmy) {
			chosenCountry.increaseArmy(in);
			rewardedArmy = rewardedArmy - in;
		}
		else {
			cout << "invalid Input" << endl;
		}
	}
}

int Player::getArmyByCountriesOwned() {

	unsigned int countryCount{ this->countries->size() };
	int rewardedArmies;

	if (countryCount <= 11) {
		rewardedArmies = 3;
	}
	else {
		rewardedArmies = countryCount / 3;
	}

	cout << "You have " << countryCount << " countries. You are rewarded " << rewardedArmies << " armies.\n";

	return rewardedArmies;
}

int Player::getArmyByContinentsOwned() {
	int rewardedArmies = 0;
	for (vector<Continent>::iterator it = continents->begin(); it != continents->end(); it++) {
		cout << it->getContinentControlExtraArmies() << " # of Army Awarded for occuping " << it->getContinentName() << " Continent." << endl;
		rewardedArmies += *(it->getContinentControlExtraArmies());
	}
	return rewardedArmies;
}

void Player::addCountry(Country c) {
	this->countries->push_back(c);
}

void Player::addContinent(Continent c) {
	this->continents->push_back(c);
}

