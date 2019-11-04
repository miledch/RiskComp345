#include "Player.h"

void PlayerDriver::run() 
{
	Player p1;
	p1.attack();

	// Change player's set of countries
	vector<Country*> countries1;
	countries1.push_back(&(Country(1, "siberia", 1)));
	countries1.push_back(&(Country(2, "worrick", 1)));
	countries1.push_back(&(Country(3, "yazteck", 1)));

	p1.changeCountries(&countries1);
	p1.printCountries();

}

void PlayerDriver::runReinforcement()
{
	//int num = 10;
	//


	//Country c1(1, "iraq1", 1);
	//Country c2(2, "iraq2", 1);
	//Country c3(3, "iraq3", 1);
	//Country c4(4, "iraq4", 1);
	//Country c5(5, "iraq5", 1);

	////Country c6(4, "syria1", 1);
	////Country c7(5, "syria2", 1);
	////Country c8(3, "Syira3", 1);
	////Country c9(4, "Syria4", 1);
	////Country c10(5, "Syria5", 1);

	//c1.increaseArmy(10);
	//c2.increaseArmy(11);
	//c3.increaseArmy(12);
	//c4.increaseArmy(13);
	//c5.increaseArmy(14);

	//vector<Country>* v = new vector<Country>();
	//v->push_back(c1);
	//v->push_back(c2);
	//v->push_back(c3);
	//v->push_back(c4);
	//v->push_back(c5);

	//Dice_Rolling_Facility* d;
	//
	//Player p(v, new Dice_Rolling_Facility(), new Hand(*(new Deck(num))));

	Map testMap;
	
	string mapFilename{ "C:\\Users\\moaya\\Documents\\GitHub\\RiskComp345\\RISK\\RISK\\maps\\ameroki.map" };
	MapLoader mapLoaderTest;

	mapLoaderTest.LoadMap(testMap, mapFilename);

	Deck deck(testMap.getCountries()->size());

	cout << testMap.getCountries()->size() << endl;

	list<Country>* cu = testMap.getCountries();
	list<Continent>* co = testMap.getcontinents();
	Player p1;

	int  i = 0;
	for (list<Country>::iterator it = cu->begin(); it != cu->end(); it++) {
		i++;
		if (i%2==0) {
			it->increaseArmy(10);
			p1.addCountry(*it);
		}
	}

	i = 0;
	for (list<Continent>::iterator it = co->begin(); it != co->end(); it++) {
		if (i < 2) {
			i++;
			p1.addContinent(*it);
		}
	}

	
	Dice_Rolling_Facility d1;
	Hand h1(deck);
	h1.draw();
	h1.draw();
	h1.draw();
	h1.draw();
	h1.draw();
	
	p1.initializeHand(&h1);
	cout << h1.getNumHandCards() << endl;

	p1.reinforce();
}

void PlayerDriver::runFortification()
{
	Map testMap;

	string mapFilename{ "C:\\Users\\moaya\\Documents\\GitHub\\RiskComp345\\RISK\\RISK\\maps\\ameroki.map" };
	MapLoader mapLoaderTest;

	mapLoaderTest.LoadMap(testMap, mapFilename);

	Deck deck(testMap.getCountries()->size());

	cout << testMap.getCountries()->size() << endl;

	list<Country>* cu = testMap.getCountries();
	list<Continent>* co = testMap.getcontinents();
	Player p1;

	int  i = 0;
	for (list<Country>::iterator it = cu->begin(); it != cu->end(); it++) {
		i++;
		if (i % 2 == 0) {
			it->increaseArmy(10);
			p1.addCountry(*it);
		}
	}

	i = 0;
	for (list<Continent>::iterator it = co->begin(); it != co->end(); it++) {
		if (i < 2) {
			i++;
			p1.addContinent(*it);
	vector<Country*> P1_countries;
	vector<Country*> P2_countries;

	// Assign the 5 countries to Player 1 and the rest of the countries to Player 2
	list<Country>::iterator c_it;
	int counter = 1;
	for (c_it = map.getCountries()->begin(); c_it != map.getCountries()->end(); ++c_it, counter++)
	{
		int nbrArmies = rand() % 5 + 1; // between 1 & 6 armies assigned randomly for each countries
		P2_countries.push_back(&*c_it);
		c_it->setCountryPlayerOwned("PLAYER 2 - DEFENDER");
		c_it->setCountryNumberArmies(nbrArmies);
		for (int x : arrP1)
		{
			if (counter == x)
			{
				c_it->setCountryPlayerOwned("PLAYER 1 - ATTACKER");
				c_it->setCountryNumberArmies(nbrArmies);
				P1_countries.push_back(&*c_it);
				
				P2_countries.pop_back();
				break;
			}
		}
	}


	Dice_Rolling_Facility d1;
	Hand h1(deck);
	h1.draw();
	h1.draw();
	h1.draw();
	h1.draw();
	h1.draw();

	p1.fortify();
}
