#include "Map.h"

Map::Map()
{
	this->continents = new list<Continent>();
	this->countries = new list<Country>();
}

void Map::add_country(int id, string name, int continent)
{
	Country country(id, name, continent);
	this->countries->push_back(country);
}

void Map::add_continents(int id, string name, int extraArmies)
{
	Continent continent(id, name, extraArmies);
	this->continents->push_back(continent);
}

list<Country>* Map::getCountries()
{
	return countries;
}

list<Continent>* Map::getcontinents()
{
	return continents;
}

void Map::ConnectedGraph()
{
	// create an array of bool the size of the number of countries
	bool* pArray = new bool[getCountries()->size()];

	// Lambda function, return true if every elem of pArray is true
	auto GraphIsConnected = [](bool* ptrArr, int arrSize)
	{
		for (int i = 0; i < arrSize; i++)
		{
			if (ptrArr[i] == false)
				return false;
		}
		// if every element of ptrArr is true, the graph is connected
		return true;
	};
	
	int countriesSize = getCountries()->size();
	// initialise each value of the array to false
	for (int i = 0; i < countriesSize; i++)
	{
		pArray[i] = false;
	}

	// while the array is not completely true at every index, keep looping through each neighbors. For example in the case of 42 countries
	// countryID goes from 1 to 42, pArray of size 42 is 0 to 41.
	// Therefore each neighbor found will tick the --ID index of the pArray. For example, country 1 has neighbors 3, 8, 18
	// pArray[2], pArray[7] & pArray[17] will be ticked to true.
	bool graphConnected = false;
	list<Country>::iterator c_it; 
	list<int>::iterator n_it; // neighbors iterator
	for (c_it = getCountries()->begin(); c_it != getCountries()->end(); ++c_it)
	{
		if (!graphConnected)
		{
			for (n_it = c_it->getNeighbors()->begin(); n_it != c_it->getNeighbors()->end(); ++n_it)
			{
				pArray[--*n_it] = true;
			}
			graphConnected = GraphIsConnected(pArray, getCountries()->size());
		}
		else if (graphConnected)
		{
			cout << "The map is a connected graph." << endl << endl;
			return;
		}
	}	
	cout << "The map is not a connected graph." << endl << endl;
}

void Map::ConnectedSubgraph()
{
	// create an array of bool the size of the number of continents
	bool* pArray = new bool[getcontinents()->size()];

	// Lambda function, return true if every elem of pArray is true
	auto SubgraphIsConnected = [](bool* ptrArr, int arrSize)
	{
		for (int i = 0; i < arrSize; i++)
		{
			if (ptrArr[i] == false)
				return false;
		}
		// if every element of ptrArr is true, the graph is connected
		return true;
	};

	int continentsSize = getcontinents()->size();
	// initialise each value of the array to false
	for (int i = 0; i < continentsSize; i++)
	{
		pArray[i] = false;
	}

	bool subgraphConnected = false;
	list<Country>::iterator c_it;
	int value;
	for (c_it = getCountries()->begin(); c_it != getCountries()->end(); ++c_it)
	{
		if (!subgraphConnected)
		{
			value = *(c_it->getCountryContinent());
			pArray[--value] = true;
			subgraphConnected = SubgraphIsConnected(pArray, getcontinents()->size());
		}
		else if (subgraphConnected)
		{
			cout << "Continents are connected subgraphs." << endl << endl;
			return;
		}
	}
	cout << "Continents is not a connected subgraphs." << endl << endl;
}

Map::~Map()
{
	// delete elements of Country => countryID, countryName, countryContinent, neighbors.
	for (std::list<Country>::iterator it = countries->begin(); it != countries->end(); ++it)
	{
		delete it->getCountryID();
		delete it->getCountryName();
		delete it->getCountryContinent();
		delete it->getNeighbors();
	}
	// delete elements of Continents => continentID, continentName.
	for (std::list<Continent>::iterator it = continents->begin(); it != continents->end(); ++it)
	{
		delete it->getContinentID();
		delete it->getContinentName();
		delete it->getContinentControlExtraArmies();
	}
	delete countries;
	delete continents;
}

Country::Country(int id, string name, int continent)
	:countryID(new int(id)), countryName(new string (name)), countryContinent(new int (continent))
{
	neighbors = new list<int>();
	playerOwned = new string("DEFAULT_PLAYER_NAME"); // when a country is created, it doesnt belong to a player yet
	numberArmies = new int(0);// when a country is created, a player hasn't put his armies on it yet
}

Country::Country(const Country& country2)
{
	countryID = new int(*country2.countryID);
	countryName = new string(*country2.countryName);
	countryContinent = new int(*country2.countryContinent);
	neighbors = new list<int>(*country2.neighbors);
	playerOwned = new string(*country2.playerOwned);
	numberArmies = new int(*country2.numberArmies);
}

Country& Country::operator=(const Country& rhs)
{
	if (this != &rhs) {
		*countryID = *(rhs.countryID);
		*countryName = *(rhs.countryName);
		*countryContinent = *(rhs.countryContinent);
		*neighbors = *(rhs.neighbors);
		*playerOwned = *(rhs.playerOwned);
		*numberArmies = *(rhs.numberArmies);
	}

	return *this;
}

void Country::displayNeighborsList()
{
	cout << "neighbors of country " << *getCountryID() << ": " << *getCountryName() << " are countries ";
	list<int>::iterator it;
	for (it = getNeighbors()->begin(); it != getNeighbors()->end(); ++it)
	{
		cout << *it << " ";
	} 
	cout << endl;
}

void Country::add_edge(string borders)
{   
	// remove the first number of the string, which represent the country ID ex: 1 20 32 2 -> 20 32 2
	borders = borders.substr(borders.find_first_of(" ") + 1);

	// Used to split string around spaces. 
	std::istringstream ss(borders);
	
	// Read each indivisual border 
	int border;
	while (ss >> border)
	{
		this->neighbors->push_back(border);
	}

}

int* Country::getCountryID()
{
	return countryID;
}

string* Country::getCountryName()
{
	return countryName;
}

int* Country::getCountryContinent()
{
	return countryContinent;
}

string* Country::getCountryPlayerOwned()
{
	return playerOwned;
}

int* Country::getCountryNumberArmies()
{
	return numberArmies;
}

list<int>* Country::getNeighbors()
{
	return neighbors;
}

// deletion of pointers member class
void Country::deleteCountry()
{
	delete countryID;
	delete countryName;
	delete countryContinent;
	delete neighbors;
}

void Country::printCountry()
{
	cout << "Country ID: " << *getCountryID() << ", Country name: " << *getCountryName() << ", belong to continent: " << *getCountryContinent()
		<< ", belong to player: " << *getCountryPlayerOwned() << ", with number of armies: " << *getCountryNumberArmies();
}

Country::~Country()
{
}

Continent::Continent(int id, string name, int continentExtraArmies)
	:continentID(new int(id)), continentName(new string(name)), continentControlExtraArmies(new int(continentExtraArmies))
{
}

int* Continent::getContinentID()
{
	return continentID;
}

string* Continent::getContinentName()
{
	return continentName;
}

int* Continent::getContinentControlExtraArmies()
{
	return continentControlExtraArmies;
}

Continent::~Continent()
{
}


