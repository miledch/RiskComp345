#pragma once
#include <vector>
#include "Player.h"
#include <algorithm>
#include <random>
#include <filesystem>
#include <fstream>
#include "MapAdapter.h"
namespace fs = std::filesystem;
class GameEngine
{
public:
	GameEngine();
	GameEngine(const GameEngine& game2);
	GameEngine& operator=(const GameEngine& rhs);
	GameEngine(int i); // for a 1 vs 1 game

	//// Getters ////
	Map* getMap() const;
	vector<Player>* getPlayers() const;
	Deck* getDeck() const;
	string* getMapPath() const;
	int* getNumOfPlayers() const;

	void startup(); // Randomizes player order, assigns countries, and assigns armies
	void runGame();
	void run1vs1();
	MapLoader* LoadLoader(Map* map, string* mapPath);

	~GameEngine();

private:
	Map* map;
	vector<Player>* players;
	Deck* deck;

	string* mapPath; // This is needed for the copy constructor
	int* numOfPlayers; // This is needed for the copy constructor

	void randomizeOrder(); // Shuffle the vector of players to randomize the order of play
	void assignCountries(); // Randomly assign countries to players in round-robin fashion
	void assignArmies(); // Players assign armies to their countries in round-robin fashion
};

class GameEngineDriver
{
public:
	static GameEngine* runGameStart();
	static GameEngine* runPlayerVsCpu();
};

