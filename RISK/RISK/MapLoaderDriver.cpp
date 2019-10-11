#include <iostream>
#include "Map.h"
#include "MapLoader.h"

using std::cout;
using std::endl;

int MapLoaderDriver::RunMapLoaderDriver()
{
	cout << "Welcome to Command Line Risk! (comp345 - Assignment 1)" << endl;

	Map map;
	MapLoader mapLoader;

	int mapStatus = 0;

	do
	{
		mapStatus = mapLoader.LoadMap(map);
	} 
	while (mapStatus == 0);
	

	// show the continents of the map
	cout << "\nThe continents of the map are " << endl;
	list<Continent>::iterator continentIt;
	for (continentIt = map.getcontinents()->begin(); continentIt != map.getcontinents()->end(); ++continentIt)
	{
		cout << *continentIt->getContinentName() << endl;
	}

	// show the countries of the map
	cout << "\nThe countries of the map are " << endl;
	list<Country>::iterator countriesIt;
	for (countriesIt = map.getCountries()->begin(); countriesIt != map.getCountries()->end(); ++countriesIt)
	{
		cout << *countriesIt->getCountryID() << ": " << *countriesIt->getCountryName() <<  endl;
	}

	list<Country>::iterator countriesIt2;
	//display the neighbors of each countries.
	cout << "\nThe neighbors of each countries are " << endl;
	for (countriesIt2 = map.getCountries()->begin(); countriesIt2 != map.getCountries()->end(); ++countriesIt2)
	{
		countriesIt2->displayNeighborsList();
	}

	


	return 0;
}

