#pragma once
#include "MapLoader.h"
#include "ConquestMapLoader.h"

class MapAdapter: public MapLoader
{
private:
	ConquestMapLoader* conquestMapLoader;
public:
	void LoadMap(Map& map, string mapName)
	{
		conquestMapLoader->LoadMap(map, mapName);
	};
	~MapAdapter() {
		delete conquestMapLoader;
		conquestMapLoader = nullptr;
	};
};
