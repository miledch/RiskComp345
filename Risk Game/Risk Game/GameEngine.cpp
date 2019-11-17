#include "GameEngine.h"

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

	// TODO: Fix cin
	int n;
	cin >> n;

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
	bool validMap = map->ConnectedGraph(); // To check if the map is a connected graph
	while (!validMap) {
		cout << "Please choose another map or enter -1 to exit" << endl;
		for (int i = 0; i < availableMaps.size(); i++)
		{
			cout << (i + 1) << ": " << availableMaps[i] << endl;
		}
		cin >> n;

		while (n > availableMaps.size() || n < 1) {
			if (cin.fail()) {
				cin.clear();
				cin.ignore(256, '\n');
			}

			if (n == -1) {
				cout << "The program will terminate immediately" << endl;
				exit(0);
			}

			cout << "Please choose a valid number or -1 to exit" << endl;
			cin >> n;
		}

		*mapPath = path + availableMaps[n - 1] + ext;
		cout << "You have chosen " << *mapPath << endl;
		delete map;
		map = new Map();
		loader.LoadMap(*map, *mapPath);
		validMap = map->ConnectedGraph();
	}

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
		players->push_back(Player(map, new vector<Country*>(), new Dice_Rolling_Facility(), new Hand(*deck), new string("Player " + to_string((i+1)))));
	}
}

GameEngine::GameEngine(int i)
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

	// TODO: Fix cin
	int n;
	cin >> n;

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
	bool validMap = map->ConnectedGraph(); // To check if the map is a connected graph
	while (!validMap) {
		cout << "Please choose another map or enter -1 to exit" << endl;
		for (int i = 0; i < availableMaps.size(); i++)
		{
			cout << (i + 1) << ": " << availableMaps[i] << endl;
		}
		cin >> n;

		while (n > availableMaps.size() || n < 1) {
			if (cin.fail()) {
				cin.clear();
				cin.ignore(256, '\n');
			}

			if (n == -1) {
				cout << "The program will terminate immediately" << endl;
				exit(0);
			}

			cout << "Please choose a valid number or -1 to exit" << endl;
			cin >> n;
		}

		*mapPath = path + availableMaps[n - 1] + ext;
		cout << "You have chosen " << *mapPath << endl;
		delete map;
		map = new Map();
		loader.LoadMap(*map, *mapPath);
		validMap = map->ConnectedGraph();
	}

	cout << "This is a 1 vs 1 game. You will play against a computer." << endl;

	int numOfCountries = map->getCountries()->size(); // Get the number of countries in the map

	deck = new Deck(numOfCountries);

	players = new vector<Player>();

	players->push_back(Player(map, new vector<Country*>(), new Dice_Rolling_Facility(), new Hand(*deck), new string("Human Player")));
	players->push_back(Player(map, new vector<Country*>(), new Dice_Rolling_Facility(), new Hand(*deck), new string("CPU Player")));
	(*players)[0].setStrategy(new HumanPlayer());
	(*players)[1].setStrategy(new AggressivePlayer());
}

GameEngine::GameEngine(const GameEngine& game2)
{
	map = new Map();
	MapLoader loader;
	this->mapPath = new string(*game2.mapPath);
	loader.LoadMap(*map, *mapPath);

	this->deck = new Deck(*game2.deck);

	this->numOfPlayers = new int(*game2.numOfPlayers);
	players = new vector<Player>();
	for (int i = 0; i < *numOfPlayers; i++) {
		players->push_back(Player((*game2.players)[i]));
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

	list<Country>* countries = map->getCountries(); // Get list of the countries

	vector<int> randomIndex(countries->size()); // Vector same size as list of countries
	for (int i = 0; i < map->getCountries()->size(); i++) {
		randomIndex[i] = i; // Initialize from 0 to length-1 of list of countries
	}
	// Then shuffle all the indexes
	shuffle(begin(randomIndex), end(randomIndex), randomEngine);

	list<Country>::iterator it = countries->begin(); // Point iterator to the beginning of list
	int j = 0;

	for (int i = 0; i < countries->size(); i++, j++) {
		if (j == *numOfPlayers) {
			j = 0; // Once j surpasses the player count, set it back to 0 (round-robin)
			cout << endl;
		}

		it = countries->begin(); // Set iterator to the beginning at each iteration
		(advance(it, randomIndex[i])); // Advance in the list to the ith element ('i' was randomized before)
		(*players)[j].getCountries()->push_back(&(*it));
		it->setCountryPlayerOwned(*((*players)[j].getName()));
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
			(*(*(*players)[i].getCountries())[j]->getCountryNumberArmies())++;
			(*(*players)[i].getAvailableArmies())--;
		}
	}

	int countryChosenIdx;
	int maxAvailableArmies = A - floor((double)(map->getCountries()->size()) / *numOfPlayers); // 'floor' to get the max value

	for (int k = 0; k < maxAvailableArmies; k++) {
		for (int i = 0; i < *numOfPlayers; i++) {

			if (*(*players)[i].getAvailableArmies() == 0) {
				continue;
			}

			cout << endl;
			cout << "(" << (*(*players)[i].getName()) << ") Place 1 army on a country (armies left: " << (*(*players)[i].getAvailableArmies()) << ")" << endl;
			for (int j = 0; j < (*players)[i].getCountries()->size(); j++) {
				cout << (j + 1) << ": " << (*(*(*players)[i].getCountries())[j]->getCountryName()) << " (armies: " << (*(*(*players)[i].getCountries())[j]->getCountryNumberArmies()) << ")" << endl;
			}

			cin >> countryChosenIdx;

			while (countryChosenIdx < 1 || countryChosenIdx >(*players)[i].getCountries()->size()) {
				cout << "Please enter a valid number" << endl;
				cin >> countryChosenIdx;
			}

			(*(*(*players)[i].getCountries())[countryChosenIdx - 1]->getCountryNumberArmies())++;
			(*(*players)[i].getAvailableArmies())--;

			cout << "You have chosen " << countryChosenIdx << ": " << (*(*(*players)[i].getCountries())[countryChosenIdx - 1]->getCountryName()) << " (armies: " << (*(*(*players)[i].getCountries())[countryChosenIdx - 1]->getCountryNumberArmies()) << ")" << endl;
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

void GameEngine::startup()
{
	randomizeOrder();
	cout << "The order of the play will be: " << endl;
	for (int i = 0; i < *numOfPlayers; i++) {
		cout << (i + 1) << ". " << *((*players)[i].getName()) << endl;
	}
	cout << endl;
	assignCountries();
	assignArmies();
}

void GameEngine::runGame() {
	string winner;
	while (true) {
		bool finished = false;
		for (int i = 0; i < (*players).size(); i++) {
			bool ownsAllCountries = true;
			cout << endl << "REINFORCEMENT PHASE: " << (*(*players)[i].getName()) << endl;
			cout << "----------------------------------------------------------------------" << endl;
			(*players)[i].reinforce();
			cout << endl << "ATTACK PHASE: " << (*(*players)[i].getName()) << endl;
			cout << "----------------------------------------------------------------------" << endl;
			(*players)[i].attack();
			cout << endl << "FORTIFYING PHASE: " << (*(*players)[i].getName()) << endl;
			cout << "----------------------------------------------------------------------" << endl;
			(*players)[i].fortify();

			ownsAllCountries = true;

			if (i == 1) {
				for (list<Country>::iterator it = (*map->getCountries()).begin(); it != (*map->getCountries()).end(); ++it) {
					*(it->getCountryPlayerOwned()) = *((*players)[i].getName());
				}
			}

			for (Country country : *(map->getCountries())) {
				if (*(country.getCountryPlayerOwned()) != *((*players)[i].getName())) {
					ownsAllCountries = false;
					break;
				}
			}
			if (ownsAllCountries == true) {
				winner = *((*players)[i].getName());
				finished = true;
				break;
			}
		}
		if (finished) {
				break;
		}
	}
	cout << winner << " owns all the countries and wins the game!" << endl;
}

void GameEngine::run1vs1() {
	string winner;
	while (true) {
		bool finished = false;
		for (int i = 0; i < (*players).size(); i++) {
			bool ownsAllCountries = true;
			/////////////////// PASTE STRATEGIES HERE

			ownsAllCountries = true;

			if (i == 1) {
				for (list<Country>::iterator it = (*map->getCountries()).begin(); it != (*map->getCountries()).end(); ++it) {
					*(it->getCountryPlayerOwned()) = *((*players)[i].getName());
				}
			}

			for (Country country : *(map->getCountries())) {
				if (*(country.getCountryPlayerOwned()) != *((*players)[i].getName())) {
					ownsAllCountries = false;
					break;
				}
			}
			if (ownsAllCountries == true) {
				winner = *((*players)[i].getName());
				finished = true;
				break;
			}
		}
		if (finished) {
			break;
		}
	}
	cout << winner << " owns all the countries and wins the game!" << endl;
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

GameEngine* GameEngineDriver::runGameStart()
{
	static GameEngine g;
	vector<PlayerObserver*> playerObservers;
	for (int i = 0; i < *(g.getNumOfPlayers()); i++) {
		playerObservers.push_back(new PlayerObserver(&(*g.getPlayers())[i]));
	}
	int numOfPlayers = *g.getNumOfPlayers();
	cout << numOfPlayers << " players have been created:" << endl;
	for (int i = 0; i < numOfPlayers; i++) {
		cout << (i+1) << ". " << (*(*g.getPlayers())[i].getName()) << endl;
	}

	list<Card> deckCards = g.getDeck()->getAllCards();
	cout << "\nThe following deck of " << deckCards.size() << " cards was created:" << endl;
	int i = 1;
	for (Card deckCard : deckCards) {
		cout << i++ << ". ";

		switch (*(deckCard.getArmyType())) {
		case 0:
			cout << "Infantry" << endl;
			break;
		case 1:
			cout << "Artillery" << endl;
			break;
		case 2:
			cout << "Cavalry" << endl;
		}
	}
	cout << endl;

	g.startup();
	g.runGame();
	return &g;
}

GameEngine* GameEngineDriver::runPlayerVsCpu() {
	static GameEngine g = new GameEngine(2);
	vector<PlayerObserver*> playerObservers;
	for (int i = 0; i < *(g.getNumOfPlayers()); i++) {
		playerObservers.push_back(new PlayerObserver(&(*g.getPlayers())[i]));
	}
	int numOfPlayers = *g.getNumOfPlayers();
	cout << numOfPlayers << " players have been created:" << endl;
	for (int i = 0; i < numOfPlayers; i++) {
		cout << (i + 1) << ". " << (*(*g.getPlayers())[i].getName()) << endl;
	}

	list<Card> deckCards = g.getDeck()->getAllCards();
	cout << "\nThe following deck of " << deckCards.size() << " cards was created:" << endl;
	int i = 1;
	for (Card deckCard : deckCards) {
		cout << i++ << ". ";

		switch (*(deckCard.getArmyType())) {
		case 0:
			cout << "Infantry" << endl;
			break;
		case 1:
			cout << "Artillery" << endl;
			break;
		case 2:
			cout << "Cavalry" << endl;
		}
	}
	cout << endl;

	g.run1vs1();

	return &g;
}
