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
	vector<Country> countries1;
	countries1.push_back(Country(1, "siberia", 1));
	countries1.push_back(Country(2, "worrick", 1));
	countries1.push_back(Country(3, "yazteck", 1));

	p1.changeCountries(&countries1);
	p1.printCountries();

}

void PlayerDriver::run2()
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
	cin >> n;
	while (n > availableMaps.size() || n < 1) {
		cout << "Please choose a valid number" << endl;
		cin >> n;
	}

	string mapPath = path + availableMaps[n - 1] + ext;
	cout << "You have chosen " << mapPath << endl;

	Map map;
	MapLoader loader;
	loader.LoadMap(map, mapPath);


	srand(time(NULL));
	// choose 5 random countries
	int arr[5];
	for (size_t i = 0; i < 5 ; i++)
	{
		arr[i] = rand() % map.getCountries()->size() + 1;
		cout << arr[i] << endl;
	}

	vector<Country> countries;

	list<Country>::iterator c_it;
	int counter = 1;
	for (c_it = map.getCountries()->begin(); c_it != map.getCountries()->end(); ++c_it, counter++)
	{
		for (int x : arr)
		{
			if (counter == x)
			{
				countries.push_back(*c_it);
			}
		}
	}

	vector<Country>::iterator it;
	for (it = countries.begin(); it != countries.end(); ++it)
	{
		cout << "COUNTRY ID: " << *it->getCountryID() << "	" << *it->getCountryName() << endl;
	}
	

	



	Player player;
	player.attack();
}
