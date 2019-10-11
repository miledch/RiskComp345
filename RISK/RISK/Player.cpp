#include "Player.h"

Player::Player() 
{

}

Player::Player(vector<Country>* c, Dice_Rolling_Facility* d, hand h)
{
	this->countries = c;
	this->dice = d;
	this 
}

Player::~Player() 
{	
	for (vector<Country>::iterator it = countries->begin(); it != countries->end(); ++it)
	{
		it->deleteCountry();
	}

}

Dice_Rolling_Facility* Player::getDice() 
{
	return this->dice;
}

void Player::printCountries() 
{
	
}

void Player::reinforce() 
{
	// number of cards given = # of countries / 3, rounded down.
	//  If the player owns all the countries of an
	//entire continent, the player is given an amount of armies corresponding to the continent’s control value.Finally, if
	//	the player owns three cards of different sorts or the same sorts, he can exchange them for armies.The number of
	//	armies a player will get for cards is first 5, then increases by 5 every time any player does so(i.e. 5, 10, 15, …).In
	//	any case, the minimal number of reinforcement armies is 3.
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

