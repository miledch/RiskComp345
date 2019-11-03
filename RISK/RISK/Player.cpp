#include "Player.h"

// Default constructor
Player::Player() 
{
	countries = new vector<Country>();
	dice = new Dice_Rolling_Facility();
	h = new Hand(*(new Deck(0)));
	name = new string("DefaultPlayer");
}

// Parameterized constructor
Player::Player(vector<Country>* c, Dice_Rolling_Facility* d, Hand* h)
{
	this->countries = c;
	this->dice = d;
	this->h = h;
	this->name = new string("DefaultPlayer");
}

Player::Player(vector<Country>* c, Dice_Rolling_Facility* d, Hand* h, string* name)
{
	this->countries = c;
	this->dice = d;
	this->h = h;
	this->name = name;
}

Player::Player(const Player& p2)
{
	this->countries = new vector<Country>(*p2.countries);
	this->dice = new Dice_Rolling_Facility(*p2.dice);
	this->h = new Hand(*p2.h);
	this->name = new string(*p2.name);
}

Player& Player::operator=(const Player& rhs)
{
	if (this != &rhs) {
		*(this->countries) = *(rhs.countries);
		*(this->dice) = *(rhs.dice);
		*(this->h) = *(rhs.h);
		*(this->name) = *(rhs.name);
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
	delete h;
	h = NULL;
	delete dice;
	dice =NULL;
	delete name;
	name = NULL;

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

string* Player::getName()
{
	return name;
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
		for (int i = 0; i < countries->size(); i++) {
			Country c = countries->at(i);
			c.printCountry();
			
		}
	}
}

void Player::reinforce() 
{
	cout << "I'm reinforcing!\n";
}

void Player::attack() 
{
	cout << "I'm attacking!\n";
}

void Player::fortify() 
{
	cout << "I'm fortifying!\n";
}

