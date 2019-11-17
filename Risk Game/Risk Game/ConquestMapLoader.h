#pragma once
#include "Map.h"


class ConquestMapLoader
{
public:
	void LoadMap(Map& map, string mapName);
	~ConquestMapLoader();
};
