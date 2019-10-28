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

	players = new vector<Player>(numOfPlayers);

	for (int i = 0; i < numOfPlayers; i++) {
		(*players)[i] = Player(new vector<Country>(), new Dice_Rolling_Facility(), new Hand(*deck));
	}
}

GameEngine& GameEngine::initiate()
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
	while (n > availableMaps.size() || n < 1) {
		cout << "Please choose a valid number" << endl;
		cin >> n;
	}

	string mapPath = path + availableMaps[n - 1] + ext;
	cout << "You have chosen " << mapPath << endl;

	Map* map = new Map();
	MapLoader loader;
	loader.LoadMap(*map, mapPath);

	int numOfPlayers;

	cout << "Please select the numbers of players in the game (2-6 players)" << endl;
	cin >> numOfPlayers;
	while (numOfPlayers < 2 || numOfPlayers > 6) {
		cout << "Please enter a valid number" << endl;
		cin >> numOfPlayers;
	}

	int numOfCountries = map->getCountries()->size(); // Get the number of countries in the map

	static GameEngine game = GameEngine(map, numOfPlayers, numOfCountries); // Create GameEngine object using constructor and return it
	return game;
}

//GameEngine::~GameEngine()
//{
//	delete map;
//	map = NULL;
//	delete players;
//	players = NULL;
//	delete deck;
//	deck = NULL;
//}
