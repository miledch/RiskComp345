#pragma once
#include "Map.h"


class MapLoader
{
public:
	string* mapName;
	int LoadMap(Map& map);
	~MapLoader();
};

class MapLoaderDriver
{
public:
	static int RunMapLoaderDriver();
};

