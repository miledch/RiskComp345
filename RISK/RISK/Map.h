#pragma once
#include <list>
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>

using std::cout;
using std::endl;
using std::list;
using std::cin;
using std::string;

// class prototype
class Country;
class Continent;

class Map
{
private:
	list<Country>* countries;
	list<Continent>* continents;
public:
	Map();
	void add_country(int id, string name, int continent);
	void add_continents(int id, string name, int extraArmies);
	list<Country>* getCountries();
	list<Continent>* getcontinents();
	void ConnectedGraph(); // for countries
	void ConnectedSubgraph();  // for contiennts
	~Map();
};

class Country
{
private:
	int* countryID;
	string* countryName;
	int* countryContinent;
	string* playerOwned;
	int* numberArmies;

	list<int>* neighbors;
public:
	Country(int, string, int);
	void displayNeighborsList();
	void add_edge(string borders);
	int* getCountryID();
	string* getCountryName();
	int* getCountryContinent();
	string* getCountryPlayerOwned();
	int* getCountryNumberArmies();
	list<int>* getNeighbors();
	void deleteCountry();
	void printCountry();

	~Country();
};

class Continent
{
private:
	int* continentID;
	string* continentName;
	int* continentControlExtraArmies;
public:
	Continent(int, string, int);
	int* getContinentID();
	string* getContinentName();
	int* getContinentControlExtraArmies();
	~Continent();
};

class MapDriver
{
public:
	int RunMapDriver();
};
