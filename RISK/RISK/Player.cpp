#include "Player.h"
#include <ctime>

// Default constructor
Player::Player()
{
	map = new Map();
	continents = new vector<Continent>();
	countries = new vector<Country*>();
	dice = new Dice_Rolling_Facility();
	h = new Hand(*(new Deck(0)));
	name = new string("DefaultPlayer");
	availableArmies = new int(0);
	viewBuffer = new vector<string>();
	newPhase = new bool(false);
}

Player::Player(Strategy* s) {
	this->strategy = s;
}


Player::Player(Map* map, vector<Country*>* c, Dice_Rolling_Facility* d, Hand* h, string* name)
{
	this->map = map;
	this->continents = new vector<Continent>();
	this->countries = c;
	this->dice = d;
	this->h = h;
	this->name = name;
	this->availableArmies = new int(0);
	this->viewBuffer = new vector<string>();
	this->newPhase = new bool(false);
}

Player::Player(const Player& p2)
{
	this->map = p2.map;
	this->continents = new vector<Continent>(*p2.continents);
	this->countries = new vector<Country*>(*p2.countries);
	this->dice = new Dice_Rolling_Facility(*p2.dice);
	this->h = new Hand(*p2.h);
	this->name = new string(*p2.name);
	this->availableArmies = new int(*p2.availableArmies);
	this->viewBuffer = new vector<string>(*p2.viewBuffer);
	this->newPhase = new bool(*p2.newPhase);
}

Player& Player::operator=(const Player& rhs)
{
	if (this != &rhs) 
	{
		this->map = rhs.map; // Make it point to the same map
		*(this->continents) = *(rhs.continents);
		*(this->countries) = *(rhs.countries);
		*(this->dice) = *(rhs.dice);
		*(this->h) = *(rhs.h);
		*(this->name) = *(rhs.name);
		*(this->availableArmies) = *(rhs.availableArmies);
		*(this->viewBuffer) = *(rhs.viewBuffer);
		*(this->newPhase) = *(rhs.newPhase);
	}
	return *this;
}

// Destructor
Player::~Player()
{
	//for (vector<Country*>::iterator it = countries->begin(); it != countries->end(); ++it)
	//{
	//	(*it)->deleteCountry();
	//}

	// Don't delete map and countries because all the players use the same map
	delete h;
	h = NULL;
	delete dice;
	dice =NULL;
	delete name;
	name = NULL;
	delete availableArmies;
	availableArmies = NULL;
	delete viewBuffer;
	viewBuffer = NULL;
	delete newPhase;
	newPhase = NULL;

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
vector<Country*>* Player::getCountries() const
{
	return this->countries;
}

string* Player::getName()
{
	return name;
}

bool* Player::getNewPhase()
{
	return newPhase;
}

int* Player::getAvailableArmies()
{
	return availableArmies;
}

vector<string>* Player::getViewBuffer()
{
	return viewBuffer;
}

void Player::setAvailableArmies(int armies)
{
	*(this->availableArmies) = armies;
}

// Change the set of player's countries
void Player::changeCountries(vector<Country*>* c)
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
		for (int i = 0; i < countries->size(); i++) 
		{
			Country c = *(countries->at(i));
			c.printCountry();
			cout << endl;
		}
	}
}

// allow player to add more arrmy in his countries at the beginning of the player turn; 

void Player::reinforce() 
{
	*newPhase = true;
	Notify2();
	*newPhase = false;
	viewBuffer->push_back("\nREINFORCEMENT PHASE: " + *name +
		"\n----------------------------------------------------------------------");
	Notify2();
	int availableArmies{ 0 };
	availableArmies = getArmyByCountriesOwned() + getArmyByContinentsOwned() + getArmyByExchangingCards();
	viewBuffer->push_back("Total # of armies rewarded is " + to_string(availableArmies));
	Notify2();
	placingArmy(availableArmies);
}

void Player::attack()
{
	*newPhase = true;
	Notify2();
	*newPhase = false;
	viewBuffer->push_back("\nATTACK PHASE: " + *name +
		"\n----------------------------------------------------------------------");
	Notify2();
	int playerDecision = 0;
	while (playerDecision != 2)
	{
		viewBuffer->push_back(*this->getName() + ", do you want to attack adjacent territories ?");
		Notify2();
		viewBuffer->push_back("Press 1 for yes or 2 for no: \n>");
		Notify2();
		HumanPlayer* p = dynamic_cast<HumanPlayer*>(strategy);
		if (p != NULL) {
			cin >> playerDecision;
		}
		else {
			playerDecision = 1;
		}
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
	vector<Country*>::iterator it;
	//The player selects one of its countries to attack from, The attacking country must have at least 2 armies on it
	do
	{
		viewBuffer->push_back("\nSelect which countries you want to attack from by entering the country ID\n");
		Notify2();

		for (it = countries->begin(); it != countries->end(); ++it)
		{
			if (*((*it)->getCountryNumberArmies()) >= 2)
			{
				viewBuffer->push_back(to_string(*(*it)->getCountryID()) + "\tCountry " + *(*it)->getCountryName() + " has " + to_string(*(*it)->getCountryNumberArmies()) + " armies available");
				Notify2();
			}
		}
		viewBuffer->push_back(">");
		Notify2();
		HumanPlayer* p = dynamic_cast<HumanPlayer*>(strategy);
		if (p != NULL) {
			cin >> countrySelected;
		}
		else {
			countrySelected = *(this->strongestCountry(*countries)->getCountryID());
		}
		for (it = countries->begin(); it != countries->end(); ++it)
		{
			if (*(*it)->getCountryNumberArmies() >= 2)
			{
				if (countrySelected == *(*it)->getCountryID())
				{
					attackCountry = &(*(*it));
					validSelection = true;
				}	
			}
		}
		if (!validSelection) {
			viewBuffer->push_back("Enter a valid country ID ");
			Notify2();
		}
	} 
	while (!validSelection);

	//find the index of the countries list corresponding to our countrySelected;
	int index;
	for (it = countries->begin(); it != countries->end(); ++it)
	{
		if (*(*it)->getCountryID() == countrySelected)
		{
			index = std::distance(countries->begin(), it);
			break;
		}
	}

	viewBuffer->push_back("\nChoose a country to attack !");
	Notify2();
	viewBuffer->push_back("Neighboring countries of country " + to_string(countrySelected) + " are:\n");
	Notify2();

	list<int>::iterator l_it;
	list<Country>::iterator countriesIt;
	vector<int> validEntryForAttack;
	for (l_it = attackCountry->getNeighbors()->begin(); l_it != attackCountry->getNeighbors()->end(); ++l_it)
	{
		for (countriesIt = map->getCountries()->begin(); countriesIt != map->getCountries()->end(); ++countriesIt)
		{
			if (*countriesIt->getCountryID() == *l_it && *countriesIt->getCountryPlayerOwned() != *attackCountry->getCountryPlayerOwned())
			{
				viewBuffer->push_back(to_string(*countriesIt->getCountryID()) + "\t" + *countriesIt->getCountryName() + " containing " + to_string(*countriesIt->getCountryNumberArmies()) + " armies.");
				Notify2();
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
		viewBuffer->push_back(">");
		Notify2();
		HumanPlayer* p = dynamic_cast<HumanPlayer*>(strategy);
		if (p != NULL) {
			cin >> attackSelection;
		}
		else {
			int index = (rand() % validEntryForAttack.size()) + 1;
			attackSelection = validEntryForAttack[index];
		}
		for (vecInt_it = validEntryForAttack.begin(); vecInt_it != validEntryForAttack.end(); vecInt_it++)
		{
			if (attackSelection == *vecInt_it)
			{
				validSelection = true;
			}
				
		}
		if (!validSelection)
		{
			viewBuffer->push_back("Please enter a valid country ID \n");
			Notify2();
			for (l_it = attackCountry->getNeighbors()->begin(); l_it != attackCountry->getNeighbors()->end(); ++l_it)
			{
				for (countriesIt = map->getCountries()->begin(); countriesIt != map->getCountries()->end(); ++countriesIt)
				{
					if (*countriesIt->getCountryID() == *l_it && *countriesIt->getCountryPlayerOwned() != *attackCountry->getCountryPlayerOwned())
					{
						viewBuffer->push_back(to_string(*countriesIt->getCountryID()) + "\t" + *countriesIt->getCountryName() + " containing " + to_string(*countriesIt->getCountryNumberArmies()) + " armies.");
						Notify2();
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
	viewBuffer->push_back("\nAttacker country " + to_string(*countries->at(index)->getCountryID()) + " " + *countries->at(index)->getCountryName() +
		" is owned by " + *countries->at(index)->getCountryPlayerOwned());
	Notify2();
	viewBuffer->push_back("Please select your number of dice to roll for your attack!");
	Notify2();
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
			viewBuffer->push_back(to_string(i) + ": " + to_string(i) + " dice");
			Notify2();
		}
		viewBuffer->push_back(">");
		Notify2();
		HumanPlayer* p1 = dynamic_cast<HumanPlayer*>(strategy);
		if (p1 != NULL) {
			cin >> attackerNbrDice;
		}
		else {
			int index =  maxDice;
			attackSelection = validEntryForAttack[index];
		}
		
		// for loop to check if the dice input is a valid selection
		for (size_t i = 1; i <= maxDice; i++)
		{
			if (attackerNbrDice == i)
			{
				validSelection = true;
				break;
			}	
		}
		if (!validSelection) {
			viewBuffer->push_back("Please enter a valid dice number");
			Notify2();
		}
	} 
	while (!validSelection);

	
	// The defender is allowed 1 to 2 dice, with the maximum number of dice being the number of armies on the defending country
	// if the defending country has 1 army, only 1 dice allowed. For 2 armies and +, then he is allowed 2 dice
	int defenderNbrDice;

	viewBuffer->push_back("\nDefender country " + to_string(*targetedCountry->getCountryID()) + " " + *targetedCountry->getCountryName() +
		" is owned by " + *targetedCountry->getCountryPlayerOwned());
	Notify2();
	if (*targetedCountry->getCountryNumberArmies() == 0)
	{
		cerr << "***This country has no armies***" << endl;
		cerr << "This is an error, not supposed to print this message";
		return;
	}
				
	viewBuffer->push_back("Please select your number of dice to roll for your defense!");
	Notify2();
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
			viewBuffer->push_back(to_string(i) + ": " + to_string(i) + " dice");
			Notify2();
		}
		viewBuffer->push_back(">");
		Notify2();
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
		if (!validSelection) {
			viewBuffer->push_back("Please enter a valid dice number");
			Notify2();
		}
	} 
	while (!validSelection);


	// Attacker rolls his dices
	vector<int> attackerRoll = this->getDice()->roll(attackerNbrDice);
	// Defender rolls his dices
	vector<int> defenderRoll = this->getDice()->roll(defenderNbrDice);
	cout << endl;
	viewBuffer->push_back(*attackCountry->getCountryPlayerOwned() + " country " + to_string(*attackCountry->getCountryID())
		+ " " + *attackCountry->getCountryName() + " rolled ");
	Notify2();
	for (vecInt_it = attackerRoll.begin(); vecInt_it != attackerRoll.end(); vecInt_it++)
	{
		viewBuffer->push_back(to_string(*vecInt_it) + " ");
		Notify2();
	}

	viewBuffer->push_back("\n" + *targetedCountry->getCountryPlayerOwned() + " country " + to_string(*targetedCountry->getCountryID())
		+ " " + *targetedCountry->getCountryName() + " rolled ");
	Notify2();
	for (vecInt_it = defenderRoll.begin(); vecInt_it != defenderRoll.end(); vecInt_it++)
	{
		viewBuffer->push_back(to_string(*vecInt_it) + " ");
		Notify2();
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

		viewBuffer->push_back("\nBecause [" + *attackCountry->getCountryPlayerOwned() + "] rolled " + to_string(attack) + " and ["
			+ *targetedCountry->getCountryPlayerOwned() + "] rolled " + to_string(defense));
		Notify2();
		//Remove one of your opponent�s army from the defending territory if the attack die is higher to its corresponding defense die.
		if (attack > defense)
		{
			targetedCountry->setCountryNumberArmies(--(*targetedCountry->getCountryNumberArmies()));
			viewBuffer->push_back("Country " + *targetedCountry->getCountryName() + " from " + *targetedCountry->getCountryPlayerOwned()
				+ " lost one army and is now at " + to_string(*targetedCountry->getCountryNumberArmies()));
			Notify2();
		}
		else // if dices are equal or defense > attack
		{
			attackCountry->setCountryNumberArmies(--(*attackCountry->getCountryNumberArmies()));
			viewBuffer->push_back("Country " + *attackCountry->getCountryName() + " from " + *attackCountry->getCountryPlayerOwned()
				+ " lost one army and is now at " + to_string(*attackCountry->getCountryNumberArmies()));
			Notify2();
		}

		// check if the attack country ran out of armies
		if (*attackCountry->getCountryNumberArmies() == 0)
		{//TODO does the program ever come inside this if statement?
			viewBuffer->push_back("The aggressor " + *attackCountry->getCountryPlayerOwned() + " has been defeated and lost country "
				+ *attackCountry->getCountryName());
			Notify2();
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
			viewBuffer->push_back("Targeted  " + *targetedCountry->getCountryPlayerOwned() + " has been defeated and lost country "
				+ *targetedCountry->getCountryName());
			Notify2();
			// player now owns the targeted countries
			countries->push_back(targetedCountry);
			Notify();
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
						viewBuffer->push_back("\nIn order to move armies to the conquered country, select a number between 1 and "
							+ to_string((*attackCountry->getCountryNumberArmies() - 1)));
						Notify2();
						viewBuffer->push_back(">");
						Notify2();
						HumanPlayer* p2 = dynamic_cast<HumanPlayer*>(strategy);
						if (p2 != NULL) {
							cin >> nbrArmies;
						}
						else {
							nbrArmies = *attackCountry->getCountryNumberArmies() - 1;
						}
						if (nbrArmies > 0 && nbrArmies < *attackCountry->getCountryNumberArmies())
							validSelection = true;
						else {
							viewBuffer->push_back("\nPlease enter a valid number");
							Notify2();
						}
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
//moving army from a contry to a neighbour counrty
void Player::fortify() 
{
	*newPhase = true;
	Notify2();
	*newPhase = false;
	viewBuffer->push_back("\nFORTIFICATION PHASE: " + *name +
		"\n----------------------------------------------------------------------");
	Notify2();
	Country* source = chosingCountrySource(); //chosing on the countires that has a neighbour(belong to the same player)
	vector<Country*> possibleTargets = ownedNieghbourCountry(*source); 
	Country* target = chooseTargetCountry(possibleTargets);// choosing the nighbouring country
	movingArmy(source, target);
}
// chosing the country that you want take army from
Country* Player::chosingCountrySource()
{
	bool t = true;
	vector<Country*> possibleSource;
	viewBuffer->push_back("Please select the country number you want to take troops from :\n");
	Notify2();
	bool check = true;
	do {
		int i = 0;
		// for loop to print out the country that a player has and has a neighbour country belong to him
		for (vector<Country*>::iterator it = countries->begin(); it != countries->end(); ++it) {
			if ( *(*it)->getCountryNumberArmies() > 1 && hasOwnedNieghbourCountry(**it)) {
				if (check) {
					Country* ptrCountry = &*(*it);
					possibleSource.push_back(ptrCountry);
				}
				viewBuffer->push_back(to_string(++i) + ". " + (*(*it)->getCountryName()) + " with " + to_string((*(*it)->getCountryNumberArmies())) + " troops.");
				Notify2();
			}
		}
		check = false;
		int in;
		HumanPlayer* p1 = dynamic_cast<HumanPlayer*>(strategy);
		if (p1 != NULL) {
			cin >> in;
		}
		else {
			AggressivePlayer* a1 = dynamic_cast<AggressivePlayer*>(strategy);
			if (a1 != NULL) {
				in = *(this->weakestCountry(*countries)->getCountryID());
			}
			else {
				in = *(this->strongestCountry(*countries)->getCountryID());
			}
		}
		
		// to check if the  is between 1 and the number of possible counties that can be part of the reinforcement
		if (in > 0 && in <= possibleSource.size()) {
			t = false;
			return (possibleSource.at(in - 1));
		}
		else {
			viewBuffer->push_back("Invalid input.\nTry again:");
			Notify2();
		}
	} while (t);
}

// return the nighbouring country(s) that i can transfer some army to 
vector<Country*> Player::ownedNieghbourCountry(Country& source)
{
	list<int>* neighboursID = source.getNeighbors();
	list<int>* myCountriesIds = new list<int>;
	for (vector<Country*>::iterator it = countries->begin(); it != countries->end(); it++)
	{
		myCountriesIds->push_back(*(*it)->getCountryID());
	}
	neighboursID->sort();
	myCountriesIds->sort();
	list<int> out;
	//taking the intersection between the list of my counties iDs and the list of neibours IDs 
	//and the result is IDs of country(s) that are neigbours owned and i can transfer troop to
	set_intersection(neighboursID->begin(), neighboursID->end(), myCountriesIds->begin(), myCountriesIds->end(), back_inserter(out));
	vector<Country*> myNeighboursPtr;
	for (list<int>::iterator it = out.begin(); it != out.end(); it++) {
		Country* CountryPtr = getCountryById(*it);
		myNeighboursPtr.push_back(CountryPtr);
	}
	return myNeighboursPtr;
}
// check if country has a country belong to same player
bool Player::hasOwnedNieghbourCountry(Country& c)
{
	vector<Country*> ownedNieghbour = ownedNieghbourCountry(c);
	return (ownedNieghbour.size() > 0);
}
//choosing the target country
Country* Player::chooseTargetCountry(vector<Country*> targets)
{
	bool t = true;
	viewBuffer->push_back("\nPlease select the country's number you want to move troops to :\n");
	Notify2();
	do {
		int i = 0;
		for (vector<Country*>::iterator it = targets.begin(); it != targets.end(); ++it) {
			viewBuffer->push_back(to_string(++i) + ". " + *(*it)->getCountryName() + " with " + to_string(*(*it)->getCountryNumberArmies()) + " troops.");
			Notify2();
		}
		int in;
		HumanPlayer* p3 = dynamic_cast<HumanPlayer*>(strategy); 
		if (p3 != NULL) {
			cin >> in;
		}
		else {
			AggressivePlayer* a3 = dynamic_cast<AggressivePlayer*>(strategy);
			if (a3 != NULL) {
				in = *(this->strongestCountry(*countries)->getCountryID());
			}
			else {
				in = *(this->weakestCountry(*countries)->getCountryID());
			}
		}
		
		if (in > 0 && in <= targets.size()) {
			t = false;
			return targets.at(in - 1);
		}
		else {
			viewBuffer->push_back("Invalid input.\nTry again:");
			Notify2();
		}
	} while (t);
}
//get the country by the ID it has 
Country* Player::getCountryById(int id)
{
	vector<Country*>::iterator it;
	for (it = countries->begin(); it != countries->end(); it++) {
		if (id == *(*it)->getCountryID()) {
			break;
		}
	}
	Country* c = &*(*it);
	return c;
}
// get method to get pointer to a country at specific index 
Country* Player::get(list<Country*> l, int index)
{
	int i = 0;
	list<Country*>::iterator it;
	for (it = l.begin(); it != l.end(); it++) {
		it++;
		if (index == i)
			break;
	}
	return *it;
}
// moves a number of armies from one country to another
void Player::movingArmy(Country* source, Country* target)
{
	bool check = true;
	while(check){
	viewBuffer->push_back("\nYou have " + to_string(*source->getCountryNumberArmies()) + " in " + *source->getCountryName() + ".");
	Notify2();
	viewBuffer->push_back("You have " + to_string(*target->getCountryNumberArmies()) + " in " + *target->getCountryName() + ".");
	Notify2();
	viewBuffer->push_back("How many you want to move from " + *source->getCountryName() + " to " + *target->getCountryName() + " .");
	Notify2();
	int in;
	HumanPlayer* p4 = dynamic_cast<HumanPlayer*>(strategy);
	if (p4 != NULL) {
		cin >> in;
	}
	else {
		AggressivePlayer* a4 = dynamic_cast<AggressivePlayer*>(strategy);
		if (a4 != NULL) {
			in = *source->getCountryNumberArmies() - 1;
		}
		else {
			in = 1;
		}
	}
	if (in > 0 && in <= (*source->getCountryNumberArmies() - 1)) {
		check = false;
		source->decreaseArmy(in);
		target->increaseArmy(in);
	}
	else if (in == 0) {
			check = false;
	}
	else {
		viewBuffer->push_back("You should leave at least one army in" + *source->getCountryName() + "\n");
		Notify2();
		continue;
	}
	viewBuffer->push_back("Now you have " + to_string(*source->getCountryNumberArmies()) + " in " + *source->getCountryName() + ".");
	Notify2();
	viewBuffer->push_back("And you have " + to_string(*target->getCountryNumberArmies()) + " in " + *target->getCountryName() + ".\n");
	Notify2();
	}
}

//calculate the number of armies that a players gets if he exchanges 3 set of matched cards
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
//placing all the armies that have been rewarded to the player at the beginning of his turn
void Player::placingArmy(int& rewardedArmy)
{
	viewBuffer->push_back("\nPlacing the Army....\n");
	Notify2();
	while (rewardedArmy != 0)
	{
		int in;
		bool check = true;
		Country* chosenCountry = new Country();
		viewBuffer->push_back("you have " + to_string(rewardedArmy) + " army(s) to place.");
		Notify2();
		do {
			viewBuffer->push_back("\nPlease select the country's number you want to reinforce:\n");
			Notify2();
			for (vector<Country*>::iterator it = countries->begin(); it != countries->end(); ++it) {
				int i = distance(countries->begin(), it);
				cout << ++i << ". " << *(*it)->getCountryName() << " with " << *(*it)->getCountryNumberArmies() << " troops." << endl;
			}
			HumanPlayer* p = dynamic_cast<HumanPlayer*>(strategy);
			if (p != NULL) {
				cin >> in;
				if (in >= 1 && in <= countries->size()) {
					check = false;
					chosenCountry = countries->at(in - 1);
				}
				else {
					viewBuffer->push_back("invalid input.");
					Notify2();
				}
			}
			else {
				AggressivePlayer* a = dynamic_cast<AggressivePlayer*>(strategy);
				if (a != NULL) {
					// aggressive 
					check = false;
					chosenCountry = this->strongestCountry(*countries);
				}
				else {
					// benevolent
					check = false;
					chosenCountry = this->weakestCountry(*countries);
				}
			}
			
		} while (check);

		HumanPlayer* p = dynamic_cast<HumanPlayer*>(strategy);
		if (p != NULL) {
			viewBuffer->push_back("choose number of army to place in " + *(chosenCountry->getCountryName()) + ".");
			Notify2();
			cin >> in;
			if (in >= 1 && in <= rewardedArmy) {
				chosenCountry->increaseArmy(in);
				rewardedArmy = rewardedArmy - in;
			}
			else {
				viewBuffer->push_back("invalid Input");
				Notify2();
			}
		}
		else {
			AggressivePlayer* a = dynamic_cast<AggressivePlayer*>(strategy);
			if (a != NULL) {
				chosenCountry->increaseArmy(rewardedArmy);
				rewardedArmy = 0;
			}
			else {
				chosenCountry->increaseArmy(1);
				rewardedArmy = rewardedArmy - 1;
			}
		}
	}
}
//calculate the number of armies that a players get according to the number of countries he has
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
//calculate the number of armies that a players get according to the number of contienet he has
int Player::getArmyByContinentsOwned() {
	int rewardedArmies = 0;
	for (vector<Continent>::iterator it = continents->begin(); it != continents->end(); it++) {
		cout << *it->getContinentControlExtraArmies() << " # of Army Awarded for occuping " << *it->getContinentName() << " Continent." << endl;
		rewardedArmies += *(it->getContinentControlExtraArmies());
	}
	return rewardedArmies;
}



//used to test the code for assignment 2
void Player::addCountry(Country* c) {
	this->countries->push_back(c);
}
//used to test the code for assignment 2
void Player::addContinent(Continent c) {
	this->continents->push_back(c);
}
//used to test the code for assignment 2
void Player::initializeHand(Hand& hand)
{
	*(this->h) = hand;
}

int Player::getNumPlayerCountries()
{
	return countries->size();
}

int Player::getNumPlayerContienent()
{
	return continents->size();
}

int Player::getNumMapCountries()
{
	return map->getCountries()->size();
}

int Player::getNumMapContienent()
{
	return map->getcontinents()->size();
}

PlayerObserver::PlayerObserver(Player* p)
{
	player = p;
	player->Attach(this);
	updateIWordPercentage();
}

PlayerObserver::~PlayerObserver()
{
	player->Detach(this);
}

void PlayerObserver::updateIWordPercentage()
{
	int numPlayerCountires = player->getNumPlayerCountries();
	this->iWorldPercentage = ((float)numPlayerCountires / player->getNumMapCountries()) * 100;
}

void PlayerObserver::Update()
{
	updateIWordPercentage();
	if (iWorldPercentage == float(0)) {
		cout << *(player->getName()) << " controls 0.0%  of the word. Game Over!" << endl;
		this->player->Detach(this);
	}
	else if (iWorldPercentage == float(100)) {
		cout << *(player->getName()) << " controls " << iWorldPercentage << "%  of the word. won the game!" << endl;
		this->player->Detach(this);
	}
	else
		cout << *(player->getName()) << " controls " << iWorldPercentage << "%  of the word."<< endl;
}

void PlayerObserver::Update2()
{
	if (*player->getNewPhase()) {
		cout << endl << "CLEARING PHASE VIEW..." << endl;
		player->getViewBuffer()->clear();
	}
	else {
		cout << player->getViewBuffer()->back() << endl;
	}
}

void Player::setStrategy(Strategy* s) {
	this->strategy = s;
}

void Player::executeStrategy() {
	this->strategy->execute(this);
}



Country* Player::strongestCountry(vector<Country*> &myCountries)
{
	Country* strong = nullptr;
	int i = 0;
	vector<Country*>::iterator it = myCountries.begin();
	for (; it != countries->end(); it++) {
		if (i == 0) {
			strong = (*it);
			i++;
		}
		if(*(*it)->getCountryNumberArmies() > *(strong->getCountryNumberArmies()))
			strong = (*it);
	}
	return strong;
}



Country* Player::weakestCountry(vector<Country*>& myCountries)
{
	Country* weak = nullptr;
	int i = 0;
	vector<Country*>::iterator it = countries->begin();
	for (; it != countries->end(); it++) {
		if (i == 0) {
			weak = (*it);
			i++;
		}
		if (*(*it)->getCountryNumberArmies() < * (weak->getCountryNumberArmies()))
			weak = (*it);
	}
	return weak;
}

void Player::fortifyToStrongest()
{
	Country* toFortify = this->strongestCountry(*countries);
	if (hasOwnedNieghbourCountry(*toFortify)) {
		vector<Country*> NieghbourCountry = ownedNieghbourCountry(*toFortify);
		Country* strongestOfOwnedNeighbour = strongestCountry(NieghbourCountry);
		if (*(strongestOfOwnedNeighbour->getCountryNumberArmies()) > 1) {
			int numOfArmyToMove = *(strongestOfOwnedNeighbour->getCountryNumberArmies()) - 1;
			cout << "Moving " << numOfArmyToMove << " from " << *(strongestOfOwnedNeighbour->getCountryName()) << " to " << *(toFortify->getCountryName()) << "." << endl;
			strongestOfOwnedNeighbour->decreaseArmy(numOfArmyToMove);
			toFortify->increaseArmy(numOfArmyToMove);
		}
		else
			cout << *(toFortify->getCountryName()) << " has " << *(toFortify->getCountryNumberArmies()) << "and can not move armyies to it ." << endl;
	}
	else
		cout << "you can not Fortify this country." << endl;
}

void Player::fortifyToWeakest()
{
	Country* toFortify = this->weakestCountry(*countries);
	if (hasOwnedNieghbourCountry(*toFortify)) {
		vector<Country*> NieghbourCountry = ownedNieghbourCountry(*toFortify);
		Country* strongestOfOwnedNeighbour = strongestCountry(NieghbourCountry);
		if (*(strongestOfOwnedNeighbour->getCountryNumberArmies()) > 1) {
			int numOfArmyToMove = *(strongestOfOwnedNeighbour->getCountryNumberArmies()) - 1;
			cout << "Moving " << numOfArmyToMove << " from " << *(strongestOfOwnedNeighbour->getCountryName()) << " to " << *(toFortify->getCountryName()) << "." << endl;
			strongestOfOwnedNeighbour->decreaseArmy(numOfArmyToMove);
			toFortify->increaseArmy(numOfArmyToMove);
		}
		else
			cout << *(toFortify->getCountryName()) << " has " << *(toFortify->getCountryNumberArmies()) << "and can not move armyies to it ." << endl;
	}
	else
		cout << "you can not Fortify this country." << endl;
}
