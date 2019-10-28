#pragma once
#include <vector>
#include "Player.h"
class GameEngine
{
public:
	GameEngine();
	GameEngine(Map* map, int numOfPlayers, int numOfCountries);

	static GameEngine& initiate();

	//~GameEngine();

private:
	Map* map;
	vector<Player>* players;
	Deck* deck;
};

