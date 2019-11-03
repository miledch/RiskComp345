#pragma once
#include <list>
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

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
	Country();
	Country(int, string, int);
	Country(const Country& country2);
	Country& operator=(const Country& rhs);
	void displayNeighborsList();
	void add_edge(string borders);
	int* getCountryID();
	string* getCountryName();
	int* getCountryContinent();
	string* getCountryPlayerOwned();
	void setCountryPlayerOwned(string playerName);
	int* getCountryNumberArmies();
	void setCountryNumberArmies(int armies);
	list<int>* getNeighbors();
	void increaseArmy(int);
	void decreaseArmy(int);
	void deleteCountry();
	void printCountintry();
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
	static int RunMapDriver();
};

