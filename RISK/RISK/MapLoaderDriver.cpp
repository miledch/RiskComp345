#include <iostream>
#include "Map.h"
#include "MapLoader.h"
#include "MapAdapter.h"
#include <vector>
#include <filesystem>
#include <fstream>

using std::cout;
using std::endl;
using std::vector;
using std::ifstream;
namespace fs = std::filesystem;

int MapLoaderDriver::RunMapLoaderDriver()
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

	string* mapPath =new string( path + availableMaps[n - 1] + ext);
	cout << "You have chosen " << mapPath << endl;

	Map* map = new Map;
	ifstream mapFile(*mapPath);
	string line;
	bool conquestMap = false;
	while (getline(mapFile, line))
	{
		if (line == "[Territories]")
			conquestMap = true;
	}
	mapFile.close();

	MapLoader* loader;
	if (conquestMap)
		loader = new MapAdapter();
	else
		loader = new MapLoader();

	loader->LoadMap(*map, *mapPath);
	delete loader;

	// show the continents of the map
	cout << "\nThe continents of the map are " << endl;
	list<Continent>::iterator continentIt;
	for (continentIt = map->getcontinents()->begin(); continentIt != map->getcontinents()->end(); ++continentIt)
	{
		cout << *continentIt->getContinentName() << endl;
	}

	// show the countries of the map
	cout << "\nThe countries of the map are " << endl;
	list<Country>::iterator countriesIt;
	for (countriesIt = map->getCountries()->begin(); countriesIt != map->getCountries()->end(); ++countriesIt)
	{
		cout << *countriesIt->getCountryID() << ": " << *countriesIt->getCountryName() <<  endl;
	}

	list<Country>::iterator countriesIt2;
	//display the neighbors of each countries.
	cout << "\nThe neighbors of each countries are " << endl;
	for (countriesIt2 = map->getCountries()->begin(); countriesIt2 != map->getCountries()->end(); ++countriesIt2)
	{
		countriesIt2->displayNeighborsList();
	}

	


	return 0;
}


