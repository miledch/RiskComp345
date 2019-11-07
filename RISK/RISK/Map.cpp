
#include "Map.h"
#include <list>

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


Graph::Graph(int countries)
{
	numCountries = countries;
	adjLists = new list<int>[countries];
	visited = new bool[countries];
	for (size_t i = 0; i < countries; i++)
	{
		visited[i] = false;
	}
}

void Graph::addEdge(int src, int dest)
{
	adjLists[src].push_front(dest);
}

bool Graph::checkVisited()
{
	bool connected = true;
	for (size_t i = 0; i < numCountries; i++)
	{
		cout << "visited[" << i << "] " << visited[i] << endl;
		if (!visited[i])
		{
			connected = false;
		}
	}
	return connected;
}

void Graph::DFS(int country)
{
	visited[country] = true;
	list<int> adjList = adjLists[country];

	list<int>::iterator i;
	for (i = adjList.begin(); i != adjList.end(); ++i)
	{
		if (!visited[*i])
		{
			DFS(*i);
		}
	}
}

bool Map::ConnectedGraph()
{
	Graph g(countries->size());

	list<Country>::iterator c_it;
	list<int>::iterator nei_it;
	for (c_it = countries->begin(); c_it != countries->end(); ++c_it)
	{
		for (nei_it = c_it->getNeighbors()->begin(); nei_it != c_it->getNeighbors()->end(); ++nei_it)
		{
			int country = *c_it->getCountryID();
			int neighbor = *nei_it;
			g.addEdge(--country, --neighbor);
		}
	}

	g.DFS(0);// checking DFS starting from country 0

	if (g.checkVisited()) {
		cout << "\nCountries are part of a connected graph\n" << endl;
		return true;
	}
	else {
		std::cerr << "\nThe map selected is not a connected graph\n" << endl;
		return false;
	}
}

void Map::ConnectedSubgraph()
{
	for (size_t i = 1; i <= continents->size(); i++)
	{
		RunConnectedSubgraph(i);
	}
}

void Map::RunConnectedSubgraph(int continentID)
{
	// need to create a graph of countries for each continents
	list<Country>* countriesPerContinent = new list<Country>();

	list<Country>::iterator c_it;
	for (c_it = countries->begin(); c_it != countries->end(); ++c_it)
	{
		if (*c_it->getCountryContinent() == continentID)
		{
			countriesPerContinent->push_back(*c_it);
		}
	}
	
	int nbrCountries = countriesPerContinent->size();
	Graph g(nbrCountries);

	list<int>::iterator nei_it;
	list<Country>::iterator countries_it;
	for (c_it = countriesPerContinent->begin(); c_it != countriesPerContinent->end(); ++c_it)
	{
		for (nei_it = c_it->getNeighbors()->begin(); nei_it != c_it->getNeighbors()->end(); ++nei_it)
		{
			for (countries_it = countries->begin(); countries_it != countries->end(); ++countries_it)
			{
				if (*countries_it->getCountryID() == *nei_it)
				{
					if (*countries_it->getCountryContinent() == continentID)
					{
						int index = std::distance(countriesPerContinent->begin(), c_it);
						int neighbor = *nei_it;
						if (continentID == 1)
							g.addEdge(index, --neighbor);
						else
						{
							neighbor = neighbor - nbrCountries;
							g.addEdge(index, --neighbor);
						}
					}
				}
			}
		}
	}

	g.DFS(0);// checking DFS starting from country 0

	if(g.checkVisited())
		cout << "\Subgraph " << continentID << " is a connected subgraph." << endl << endl;
	else
		std::cerr << "\Subgraph " << continentID << " is not a connected subgraph." << endl << endl;
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
	countries = nullptr;
	continents = nullptr;
}

Country::Country()
{
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

void Country::setCountryPlayerOwned(string playerName)
{
	playerOwned = new string(playerName);
}

int* Country::getCountryNumberArmies()
{
	return numberArmies;
}

void Country::setCountryNumberArmies(int armies)
{
	numberArmies = new int(armies);
}

list<int>* Country::getNeighbors()
{
	return neighbors;
}

void Country::increaseArmy(int add)
{
	*this->numberArmies += add;
}

void Country::decreaseArmy(int minus)
{
	*this->numberArmies -= minus;
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


