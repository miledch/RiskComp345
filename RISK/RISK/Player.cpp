#include "Player.h"

// Default constructor
Player::Player() {}

// Parameterized constructor
Player::Player(vector<Country>* c, Dice_Rolling_Facility* d, Hand* h)
{
	this->countries = c;
	this->dice = d;
	this->h = h;
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

