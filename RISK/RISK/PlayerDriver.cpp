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

void PlayerDriver::runReinforcement()
{
	int num = 10;
	


	Country c1(1, "iraq1", 1);
	Country c2(2, "iraq2", 1);
	Country c3(3, "iraq3", 1);
	Country c4(4, "iraq4", 1);
	Country c5(5, "iraq5", 1);



	c1.increaseArmy(10);
	c2.increaseArmy(11);
	c3.increaseArmy(12);
	c4.increaseArmy(13);
	c5.increaseArmy(14);

	vector<Country>* v = new vector<Country>();
	v->push_back(c1);
	v->push_back(c2);
	v->push_back(c3);
	v->push_back(c4);
	v->push_back(c5);

	Dice_Rolling_Facility* d;

	Player p(v, new Dice_Rolling_Facility(), new Hand(*(new Deck(num))));

	cout << p.getArmyByExchangingCards() << endl;
	cout << p.getArmyByContinentsOwned() << endl;
	cout << p.getArmyByCountriesOwned() << endl;
	p.reinforce();


}
