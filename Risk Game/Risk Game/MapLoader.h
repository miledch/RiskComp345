#pragma once
#include "Map.h"


class MapLoader
{
public:
	virtual void LoadMap(Map& map, string mapName);
	virtual ~MapLoader();
};

class MapLoaderDriver
{
public:
	static int RunMapLoaderDriver();
	bool static ConquestMap();
};

