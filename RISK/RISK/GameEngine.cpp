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
	if (cin.fail()) {
		cin.clear();
		cin.ignore(256, '\n');
	}
	while (n > availableMaps.size() || n < 1) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
		}
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

	players = new vector<Player>();

	for (int i = 0; i < *numOfPlayers; i++) {
		players->push_back(Player(map, new vector<Country>(), new Dice_Rolling_Facility(), new Hand(*deck), new string("Player " + to_string((i+1)))));
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

void GameEngine::randomizeOrder()
{
	random_device rd;
	auto randomEngine = default_random_engine{ rd() };
	shuffle(begin(*players), end(*players), randomEngine);
}

void GameEngine::assignCountries()
{
	random_device rd;
	auto randomEngine = default_random_engine{ rd() };

	list<Country> countries = *(map->getCountries()); // Get list of the countries

	vector<int> randomIndex(countries.size()); // Vector same size as list of countries
	for (int i = 0; i < map->getCountries()->size(); i++) {
		randomIndex[i] = i; // Initialize from 0 to length-1 of list of countries
	}
	// Then shuffle all the indexes
	shuffle(begin(randomIndex), end(randomIndex), randomEngine);

	list<Country>::iterator it = countries.begin(); // Point iterator to the beginning of list
	int j = 0;

	for (int i = 0; i < countries.size(); i++, j++) {
		if (j == *numOfPlayers) {
			j = 0; // Once j surpasses the player count, set it back to 0 (round-robin)
			cout << endl;
		}

		it = countries.begin(); // Set iterator to the beginning at each iteration
		(advance(it, randomIndex[i])); // Advance in the list to the ith element ('i' was randomized before)
		(*players)[j].getCountries()->push_back(*it);
		cout << *(it->getCountryName()) << " has been assigned to " << *(*players)[j].getName() << endl;
	}
}

void GameEngine::assignArmies()
{
	int A; // # of armies per player

	switch (*numOfPlayers) {
	case 2:
		A = 40;
		break;
	case 3:
		A = 35;
		break;
	case 4:
		A = 30;
		break;
	case 5:
		A = 25;
		break;
	case 6:
		A = 20;
	}

	for (int i = 0; i < *numOfPlayers; i++) {
		(*players)[i].setAvailableArmies(A);
	}

	for (int i = 0; i < (*players).size(); i++) {
		for (int j = 0; j < (*(*players)[i].getCountries()).size(); j++) {
			(*(*(*players)[i].getCountries())[j].getCountryNumberArmies())++;
			(*(*players)[i].getAvailableArmies())--;
		}
	}

	int countryChosenIdx;
	int maxAvailableArmies = A - ceil(((double)(map->getCountries()->size()) / *numOfPlayers)); // 'ceil' to get the max value

	for (int k = 0; k < maxAvailableArmies; k++) {
		for (int i = 0; i < *numOfPlayers; i++) {

			if ((*players)[i].getAvailableArmies() == 0) {
				continue;
			}

			cout << endl;
			cout << "(" << (*(*players)[i].getName()) << ") Place 1 army on a country (armies left: " << (*(*players)[i].getAvailableArmies()) << ")" << endl;
			for (int j = 0; j < (*players)[i].getCountries()->size(); j++) {
				cout << (j + 1) << ": " << (*(*(*players)[i].getCountries())[j].getCountryName()) << " (armies: " << (*(*(*players)[i].getCountries())[j].getCountryNumberArmies()) << ")" << endl;
			}

			cin >> countryChosenIdx;

			while (countryChosenIdx < 1 || countryChosenIdx >(*players)[i].getCountries()->size()) {
				cout << "Please enter a valid number" << endl;
				cin >> countryChosenIdx;
			}

			(*(*(*players)[i].getCountries())[countryChosenIdx - 1].getCountryNumberArmies())++;
			(*(*players)[i].getAvailableArmies())--;

			cout << "You have chosen " << countryChosenIdx << ": " << (*(*(*players)[i].getCountries())[countryChosenIdx - 1].getCountryName()) << " (armies: " << (*(*(*players)[i].getCountries())[countryChosenIdx - 1].getCountryNumberArmies()) << ")" << endl;
		}
	}
}

Map* GameEngine::getMap() const
{
	return map;
}

vector<Player>* GameEngine::getPlayers() const
{
	return players;
}

Deck* GameEngine::getDeck() const
{
	return deck;
}

string* GameEngine::getMapPath() const
{
	return mapPath;
}

int* GameEngine::getNumOfPlayers() const
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
	delete mapPath;
	mapPath = NULL;
	delete numOfPlayers;
	numOfPlayers = NULL;
}
