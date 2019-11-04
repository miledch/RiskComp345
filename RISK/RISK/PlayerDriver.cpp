#include "Player.h"
#include <filesystem>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
namespace fs = std::filesystem;

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

	vector<Country*>* v = new vector<Country*>();
	v->push_back(&c1);
	v->push_back(&c2);
	v->push_back(&c3);
	v->push_back(&c4);
	v->push_back(&c5);

	Dice_Rolling_Facility* d;

	Player p(new Map(), v, new Dice_Rolling_Facility(), new Hand(*(new Deck(num))), new string("Default"));

	cout << p.getArmyByExchangingCards() << endl;
	cout << p.getArmyByContinentsOwned() << endl;
	cout << p.getArmyByCountriesOwned() << endl;
	p.reinforce();

}

void PlayerDriver::runAttackPhase()
{
	cout << "Welcome to the Command Line Risk Game!\n" << endl;

	string path("maps/");
	string ext(".map");
	vector<string> availableMaps;

	for (auto& p : fs::recursive_directory_iterator(path))
	{
		if (p.path().extension() == ext)
			availableMaps.push_back(p.path().stem().string());
	}

	cout << "Please select a map from the following list:" << endl;

	for (int i = 0; i < availableMaps.size(); i++)
	{
		cout << (i + 1) << ": " << availableMaps[i] << endl;
	}

	int n;
	cout << ">";
	cin >> n;
	while (n > availableMaps.size() || n < 1) {
		cout << "Please choose a valid number" << endl;
		cout << ">";
		cin >> n;
	}

	string mapPath = path + availableMaps[n - 1] + ext;
	cout << "You have chosen " << mapPath << endl;

	Map map;
	MapLoader loader;
	loader.LoadMap(map, mapPath);


	srand(time(NULL));
	// choose 5 random countries for player 1
	int arrP1[5];
	for (size_t i = 0; i < 5 ; i++)
	{
		arrP1[i] = rand() % map.getCountries()->size() + 1;
	}

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

	//Creation of a Players object
	Player player1(&map, &P1_countries, new Dice_Rolling_Facility(), new Hand(), new string("Player 1"));
	Player player2(&map, &P2_countries, new Dice_Rolling_Facility(), new Hand(), new string("Player 2"));
	
	player1.attack();

}
