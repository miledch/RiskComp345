#include "GameEngine.h"
#include <filesystem>
namespace fs = std::filesystem;

GameEngine::GameEngine()
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

	mapPath = new string(path + availableMaps[n - 1] + ext);
	cout << "You have chosen " << *mapPath << endl;

	map = new Map();
	MapLoader loader;
	loader.LoadMap(*map, *mapPath);

	numOfPlayers = new int;
	cout << "Please select the numbers of players in the game (2-6 players)" << endl;
	cin >> (*numOfPlayers);
	while (*numOfPlayers < 2 || *numOfPlayers > 6) {
		cout << "Please enter a valid number" << endl;
		cin >> *numOfPlayers;
	}

	int numOfCountries = map->getCountries()->size(); // Get the number of countries in the map

	deck = new Deck(numOfCountries);

	players = new vector<Player>(*numOfPlayers);

	for (int i = 0; i < *numOfPlayers; i++) {
		(*players)[i] = Player(new vector<Country>(), new Dice_Rolling_Facility(), new Hand(*deck));
	}
}

GameEngine::GameEngine(const GameEngine& game2)
{
	map = new Map();
	MapLoader loader;
	this->mapPath = new string(*game2.mapPath);
	loader.LoadMap(*map, *mapPath);

	this->deck = new Deck(*game2.deck);

	this->numOfPlayers = new int(*game2.numOfPlayers);
	players = new vector<Player>(*numOfPlayers);
	for (int i = 0; i < *numOfPlayers; i++) {
		(*players)[i] = Player((*players)[i]);
	}
}

GameEngine& GameEngine::operator=(const GameEngine& rhs)
{
	if (this != &rhs) {
		*map = *(rhs.map);
		*players = *(rhs.players);
		*deck = *(rhs.deck);

		*mapPath = *(mapPath);
		*numOfPlayers = *(rhs.numOfPlayers);
	}

	return *this;
}

const Map* GameEngine::getMap() const
{
	return map;
}

const vector<Player>* GameEngine::getPlayers() const
{
	return players;
}

const Deck* GameEngine::getDeck() const
{
	return deck;
}

const string* GameEngine::getMapPath() const
{
	return mapPath;
}

const int* GameEngine::getNumOfPlayers() const
{
	return numOfPlayers;
}

void GameEngine::runGame() {
	while (true) {
		for (int i = 0; i < (*players).size(); i++) {
			(*players)[i].reinforce();
			(*players)[i].attack();
			(*players)[i].fortify();
		}
	}
}

GameEngine::~GameEngine()
{
	delete map;
	map = NULL;
	delete players;
	players = NULL;
	delete deck;
	deck = NULL;
}
