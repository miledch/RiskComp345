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
	GameEngine(bool tournament);
	GameEngine(const GameEngine& game2);
	GameEngine& operator=(const GameEngine& rhs);
	GameEngine(int i); // for a 1 vs 1 game
	GameEngine(vector<string> playerStr, string mapStr );

	//// Getters ////
	Map* getMap() const;
	vector<Player>* getPlayers() const;
	Deck* getDeck() const;
	string* getMapPath() const;
	int* getNumOfPlayers() const;
	vector<string>* getSelectedMapsPath() const;


	void startup(); // Randomizes player order, assigns countries, and assigns armies
	void runGame();
	
	void run1vs1();
	MapLoader* LoadLoader(string* mapPath);

	inline int choosingNumOfMaps();
	void choosingNumOfPlayers();
	void selectingMaps(int&); // for tournament
	void loadTournamentMaps(string mapPath); // for tournament
	
	void choosingNumOfMaxTurns();
	void choosingNumOfGames();
	void startupCpu(int);
	void runGameCpu(int, vector<string>& );
	bool isIncludeHuman();
	void createPlayers(vector<string>& , string);
	void assignCountries(int); // Randomly assign countries to players in round-robin fashion
	void assignArmies(int);
	~GameEngine();

private:
	Map* map;
	vector<Player>* players;
	Deck* deck;
	

	string* mapPath; // This is needed for the copy constructor
	int* numOfPlayers; // This is needed for the copy constructor

	void randomizeOrder(); // Shuffle the vector of players to randomize the order of play
	 // Players assign armies to their countries in round-robin fashion

	void autoPlaceArmies(int); /* Place armies automatically in the startup phase 
							 instead of choosing manually */

	int *numOfMaxTurns;
	int *numOfGames;
	vector<string>* selectedMapsPath;
	vector<string>* remainingMaps;
	vector<string>* winners;

};


class GameEngineDriver : public GameEngine
{
public:
	static GameEngine* runGameStart1();
	static void runTournamentStart1();
	static GameEngine* runModeSelection1();
	static GameEngine* runPlayerVsCpu();
	static MapLoader* LoadLoader(string& mapPath);
};