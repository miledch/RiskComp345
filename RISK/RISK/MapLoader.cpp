#include "MapLoader.h"
#include <fstream>

using std::ifstream;

int MapLoader::LoadMap(Map& map, string mapName)
{
	ifstream mapFile(mapName);

	if (mapFile.fail())
	{
		cout << "File does not exist" << endl;
		cout << "Double check the name of the map file" << endl;
		return 0;// exit the load method
	}

	bool storeContinents = false;
	bool storeCountries = false;
	bool storeNeighbors = false;
	int continentID = 0; // must pass ++continentID as a param because it should start at 1
	string line;
	string wordsContinent[2]; // to store continent name, extra armies per continent control
	string wordsCountry[3]; // to store countryID, country name, the continent associated

	list<Country>::iterator it;

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
			int i = 0;
			while (ssin.good() && i < 2)
			{
				ssin >> wordsContinent[i];
				++i;
			}
			map.add_continents(++continentID, wordsContinent[0],stoi(wordsContinent[1]));// ID, continent, extra armies per continent control
		}
		else if (storeCountries)
		{
			if (line.length() == 0)
			{
				storeCountries = false;
				continue;
			}
			std::stringstream ssin(line);
			int i = 0;
			while (ssin.good() && i < 3) 
			{
				ssin >> wordsCountry[i];
				++i;
			}
			map.add_country(stoi(wordsCountry[0]), wordsCountry[1], stoi(wordsCountry[2]));// ID, country, continentID
		}
		else if (storeNeighbors)
		{
			if (line.length() == 0)
			{
				storeNeighbors = false;
				continue;
			}
			
			it->add_edge(line); // add_edge method already handle the spliting of the string
			std::advance(it, 1);
		}
		if (line == "[continents]")
		{
			storeContinents = true;
		}
		if (line == "[countries]")
		{
			storeCountries = true;
		}
		if (line == "[borders]")
		{
			it = map.getCountries()->begin();
			storeNeighbors = true;
		}
	}
	return 1;
}

MapLoader::~MapLoader()
{
}

