#include "ConquestMapLoader.h"
#include <fstream>
#include <vector>
#include <filesystem>

using std::ifstream;
using std::vector;

void ConquestMapLoader::LoadMap(Map& map, string mapName)
{
	ifstream mapFile(mapName);

	if (mapFile.fail())
	{
		cout << "File does not exist" << endl;
		cout << "Double check the name of the map file" << endl;
		return;// exit the load method
	}

	bool storeContinents = false;
	bool storeTerritories = false;
	bool storeNeighbors = false;
	int continentID = 0; // must pass ++continentID as a param because it should start at 1
	int countryID = 1;
	string line;
	string wordsContinent[2]; // to store continent name, extra armies per continent control
	string wordsCountry[4]; // to store countryID, country name, the continent associated
	vector<vector<string>> wordsNeighbors(100); //MAXIMUM OF 100 COUNTRIES

	list<Continent>::iterator continentIt;

	while (getline(mapFile, line))
	{
		if (storeContinents)
		{
			if (line.length() == 0)
			{
				storeContinents = false;
				continue;
			}
			//continent = line.substr(0, line.find(" "));// returns the first word of the string, which is the continent name
			std::stringstream ssin(line);
			string token;
			int i = 0;
			while (getline(ssin, token, '=') && i < 2)
			{
				 wordsContinent[i] = token;
				++i;
			}
			map.add_continents(++continentID, wordsContinent[0], stoi(wordsContinent[1]));// ID, continent, extra armies per continent control
		}
		else if (storeTerritories)
		{
			if (line.length() == 0)
			{
				continue;// go to the next line
			}
			std::stringstream ssin(line);
			string token;
			int i = 0;
			while (getline(ssin, token, ','))
			{
				if(i <= 3)
					wordsCountry[i] = token;
				else if (i > 3)
				{
					wordsNeighbors[countryID].push_back(token);
				}
				++i;
			}
			for (continentIt = map.getcontinents()->begin(); continentIt != map.getcontinents()->end(); ++continentIt)
			{
				if (*continentIt->getContinentName() == wordsCountry[3])
				{
					continentID = *continentIt->getContinentID();
				}
			}
			map.add_country(countryID++, wordsCountry[0], continentID);// ID, country, continentID
		}
		if (line == "[Continents]")
		{
			storeContinents = true;
		}
		if (line == "[Territories]")
		{
			storeTerritories = true;
		}
	}
	mapFile.close();
	// once we reach end of file, create the neighbors for each country
	//map.getCountries()->back().add_ConquestEdge(wordsNeighbors, map);
	list<Country>::iterator it;
	int i = 1;
	for (it = map.getCountries()->begin(); it != map.getCountries()->end(); ++it, ++i)
	{
		it->add_ConquestEdge(wordsNeighbors[i], *map.getCountries());
	}
}



ConquestMapLoader::~ConquestMapLoader()
{
}
