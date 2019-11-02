#include "Player.h"

// Default constructor
Player::Player()
{
	countries = new vector<Country>();
	dice = new Dice_Rolling_Facility();
	h = new Hand(*(new Deck(0)));
}

// Parameterized constructor
Player::Player(vector<Country>* c, Dice_Rolling_Facility* d, Hand* h)
{
	this->countries = c;
	this->dice = d;
	this->h = h;
}

Player::Player(const Player& p2) 
{
	this->countries = new vector<Country>(*p2.countries);
	this->dice = new Dice_Rolling_Facility(*p2.dice);
	//this->h = new Hand(p2.h);
}

Player& Player::operator=(const Player& rhs)
{
	if (this != &rhs) {
		*(this->countries) = *(rhs.countries);
		*(this->dice) = *(rhs.dice);
		(this->h) = (rhs.h);
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
	//delete h;
	//h = NULL;
	delete dice;
	dice =NULL;

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
vector<Country>* Player::getCountries() 
{
	return this->countries;
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
	}
}

void Player::reinforce() 
{
	cout << "I'm reinforcing!\n";
	int availableArmies{0};
	availableArmies = getArmyByCountriesOwned() + getArmyBycontienetOwned() + getArmyByExchangingCards();
	cout << "Total # of arnies rewarded is " << availableArmies << "." << endl;
	placingArmy(availableArmies);
}

void Player::attack() 
{
	cout << "I'm attacking!\n";
}

void Player::fortify() 
{
	cout << "I'm fortifying!\n";
	Country* source = &(chosingCountrySource());
	list<Country*> possibleTargets = ownedNieghbourCountry(*source);
	Country* target = chooseTargetCountry(possibleTargets);
	movingArmy(source,target);
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

list<Country*> Player::ownedNieghbourCountry(Country &source)
{
	list<int>* neighboursID = source.getNeighbors();
	list<int>* myCountriesIds;
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

bool Player::hasOwnedNieghbourCountry(Country &c)
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
		for (list<Country>::iterator it = targets.begin ; it != targets.end; ++it) {
				cout << ++i << ". " << *it->getCountryName() << " with " << it->getCountryNumberArmies() << "  troops." << endl;
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
		list<int>::iterator it = l.begin;
		for (int i = 0; i < index; i++) {
			++it;
		}
		return getCountryById(*it);
}

void Player::movingArmy(Country* source, Country* target)
{
	cout << "you have " << source->getCountryNumberArmies() << "in" << source->getCountryName() << ".\n";
	cout << "you have " << target->getCountryNumberArmies() << "in" << target->getCountryName() << ".\n";
	cout << "how many you want to move from " << source->getCountryName() << " to " << target->getCountryName() <<" ."<<endl;
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

	while (doExchange){
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

void Player::placingArmy(int &rewardedArmy)
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

int Player::getArmyBycontienetOwned(){
	int rewardedArmies = 0;
	for (vector<Continent>::iterator it = continents->begin(); it != continents->end(); it++) {
		cout << it->getContinentControlExtraArmies() << " # of Army Awarded for occuping " << it->getContinentName() <<" Continent." << endl;
		rewardedArmies += *(it->getContinentControlExtraArmies());
	}
	return rewardedArmies;
}

