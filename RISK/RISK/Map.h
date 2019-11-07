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
	bool ConnectedGraph(); // for countries
	void ConnectedSubgraph();
	void RunConnectedSubgraph(int continentID);  // for contiennts
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
	void deleteCountry();
	void printCountry();
	void decreaseArmy(int);
	void increaseArmy(int);

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

// this class is used for the Depth First search in connectedGraph
class Graph
{
	int numCountries;
	list<int>* adjLists;
	bool* visited;

public:
	Graph(int V);
	void addEdge(int src, int dest);
	void DFS(int vertex);
	bool checkVisited();
	bool checkVisitedSubGraph(list<Country> countriesPerContinent);
	~Graph();
};


class MapDriver
{
public:
	static int RunMapDriver();
};

