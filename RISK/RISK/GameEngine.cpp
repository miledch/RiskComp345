#include "GameEngine.h"
#include <filesystem>
namespace fs = std::filesystem;

GameEngine::GameEngine()
{
	map = new Map();
	players = new vector<Player>();
	deck = new Deck(0);
}

GameEngine::GameEngine(Map* map, int numOfPlayers, int numOfCountries)
{
	this->map = map;
	deck = new Deck(numOfCountries);

	players = new vector<Player>();

	for (int i = 0; i < numOfPlayers; i++) {
		players->push_back(Player(new vector<Country>(), new Dice_Rolling_Facility(), new Hand(*deck)));
	}
}

void GameEngine::initiate()
{
	cout << "Welcome to the Command Line Risk Game!\n" << endl;

	string path("maps/");
	string ext(".map");
	vector<string> availableMaps;

	for (auto& p : fs::recursive_directory_iterator(path))
	{
		if (p.path().extension() == ext)
			availableMaps.push_back(p.path().stem().string());
	}

	cout << "Please select a map from the following list:" << endl;

	for (int i = 0; i < availableMaps.size(); i++)
	{
		cout << (i + 1) << ": " << availableMaps[i] << endl;
	}

	int n;
	cin >> n;
	string map = path + availableMaps[n - 1] + ext;
	cout << "You have chosen " << map;
}
