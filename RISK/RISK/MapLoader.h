#pragma once
#include "Map.h"


class MapLoader
{
public:
	int LoadMap(Map& map, string mapName);
	~MapLoader();
};

class MapLoaderDriver
{
public:
	static int RunMapLoaderDriver();
};

