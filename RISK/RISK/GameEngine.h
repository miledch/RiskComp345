#pragma once
#include <vector>
#include "Player.h"
class GameEngine
{
public:
	GameEngine();
	GameEngine(const GameEngine& game2);
	GameEngine& operator=(const GameEngine& rhs);

	//// Getters: Return the actual pointers but return them as const so you can't change the values ////
	const Map* getMap() const;
	const vector<Player>* getPlayers() const;
	const Deck* getDeck() const;
	const string* getMapPath() const;
	const int* getNumOfPlayers() const;

	~GameEngine();

private:
	Map* map;
	vector<Player>* players;
	Deck* deck;

	string* mapPath; // This is needed for the copy constructor
	int* numOfPlayers; // This is needed for the copy constructor
};

