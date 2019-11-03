#pragma once
#include <vector>
#include "Player.h"
#include <algorithm>
#include <random>
class GameEngine
{
public:
	GameEngine();
	GameEngine(const GameEngine& game2);
	GameEngine& operator=(const GameEngine& rhs);

	void randomizeOrder(); // Shuffle the vector of players to randomize the order of play
	void assignCountries(); // Randomly assign countries to players in round-robin fashion
	void assignArmies(); // Players assign armies to their countries in round-robin fashion

	void runGame();

	//// Getters ////
	Map* getMap() const;
	vector<Player>* getPlayers() const;
	Deck* getDeck() const;
	string* getMapPath() const;
	int* getNumOfPlayers() const;

	~GameEngine();

private:
	Map* map;
	vector<Player>* players;
	Deck* deck;

	string* mapPath; // This is needed for the copy constructor
	int* numOfPlayers; // This is needed for the copy constructor
};

