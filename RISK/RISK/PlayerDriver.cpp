#include "Player.h"

void PlayerDriver::run() 
{
	Player p1;
	p1.attack();

	// Change player's set of countries
	vector<Country> countries1;
	countries1.push_back(Country(1, "siberia", 1));
	countries1.push_back(Country(2, "worrick", 1));
	countries1.push_back(Country(3, "yazteck", 1));

	p1.changeCountries(&countries1);
	p1.printCountries();

}