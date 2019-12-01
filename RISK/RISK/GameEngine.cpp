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

	// TODO: Fix cin, if you enter "1k" for example it's valid even though "1k" is a string
	int n;
	cin >> n;

	while (n > availableMaps.size() || n < 1) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Please choose a valid number" << endl;
		cin >> n;
	}
	cin.clear();
	cin.ignore(256, '\n');

	mapPath = new string(path + availableMaps[n - 1] + ext);
	cout << "You have chosen " << *mapPath << endl;

	map = new Map();
	MapLoader* loader = LoadLoader(map, mapPath);// LoadLoader will load the correct map between domination and conquest map types
	loader->LoadMap(*map, *mapPath);
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
		loader = LoadLoader(map, mapPath);// LoadLoader will load the correct map between domination and conquest map types
		loader->LoadMap(*map, *mapPath);
		validMap = map->ConnectedGraph(); // To check if the map is a connected graph
	}

	delete loader;

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

GameEngine::GameEngine(bool tournament) :numOfPlayers(0)
{
	int mapsNum = choosingNumOfMaps();
	selectingMaps(mapsNum);
	//choosingNumOfPlayers();
	//choosingNumOfGames();
	//choosingNumOfMaxTurns();
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
	 
	// TODO:maybe Fixed hahahhahaha cin
	int n;
	cin >> n;
	bool valid = false;
	while (!valid) {
		if (n > 0 || n <= availableMaps.size() ) {
			valid = true;
		}else{
		cout << "Please choose a valid number" << endl;
		cin >> n;
		}
	}

	mapPath = new string(path + availableMaps[n - 1] + ext);
	cout << "You have chosen " << *mapPath << endl;

	map = new Map();
	MapLoader* loader = LoadLoader(map, mapPath);// LoadLoader will load the correct map between domination and conquest map types
	loader->LoadMap(*map, *mapPath);
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
		loader = LoadLoader(map, mapPath);// LoadLoader will load the correct map between domination and conquest map types
		loader->LoadMap(*map, *mapPath);
		validMap = map->ConnectedGraph(); // To check if the map is a connected graph
	}

	delete loader;

	cout << "This is a 1 vs 1 game. You will play against a computer." << endl;

	int numOfCountries = map->getCountries()->size(); // Get the number of countries in the map

	deck = new Deck(numOfCountries);

	players = new vector<Player>();
	numOfPlayers = new int(2);

	players->push_back(Player(map, new vector<Country*>(), new Dice_Rolling_Facility(), new Hand(*deck), new string("Human Player")));
	players->push_back(Player(map, new vector<Country*>(), new Dice_Rolling_Facility(), new Hand(*deck), new string("CPU Player")));
	HumanPlayer* p1 = new HumanPlayer();
	AggressivePlayer* p2 = new AggressivePlayer();
	(*players)[0].setStrategy(p1);
	(*players)[1].setStrategy(p2);
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
		(*players)[j].Notify();
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
		(*players)[i].setAvailableArmies(A); // # of armies that each player has left to place
	}

	for (int i = 0; i < (*players).size(); i++) { // Assign 1 army to each country for all players
		for (int j = 0; j < (*(*players)[i].getCountries()).size(); j++) {
			(*(*(*players)[i].getCountries())[j]->getCountryNumberArmies())++;
			(*(*players)[i].getAvailableArmies())--;
		}
	}

	int decision;
	cout << "\nDo you want to place armies manually or automatically?" << endl;
	cout << "1. Manually " << endl;
	cout << "2. Automatically " << endl;
	cin >> decision;
	while (decision != 1 && decision != 2) {
		cout << "Invalid input. Try again" << endl;
		cin >> decision;
	}

	if (decision == 1) {

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
	else {
		this->autoPlaceArmies();
	}
}

void GameEngine::autoPlaceArmies()
{
	int firstCountryArmies; // Each player's first country will have 30% of its total armies to begin with
	int secondCountryArmies; // Each player's second country will have 20% of its total armies to begin with
	int randArmies; // The 50% of armies left will be placed randomly
	int* availableArmies;

	for (int i = 0; i < *numOfPlayers; i++) {
		availableArmies = (*players)[i].getAvailableArmies();
		vector<int> randomCountries(*availableArmies);
		firstCountryArmies = (*(*players)[i].getAvailableArmies()) * 0.3;
		secondCountryArmies = (*(*players)[i].getAvailableArmies()) * 0.2;
		(*(*(*players)[i].getCountries())[0]->getCountryNumberArmies()) += firstCountryArmies;
		(*(*(*players)[i].getCountries())[1]->getCountryNumberArmies()) += secondCountryArmies;
		*availableArmies -= (firstCountryArmies + secondCountryArmies);
		int size = (*players)[i].getNumPlayerCountries();
		for (int j = 0; j < *availableArmies; j++) {
			randomCountries[j] = rand() % size; // Get random countries indexes
		}
		// Repeat it for however many number of armies we have left to place
		for (int j = 0; j < *availableArmies; j++) { // Increment # of armies in countries using those random indexes
			(*(*(*players)[i].getCountries())[randomCountries[j]]->getCountryNumberArmies())++;
		}
		*availableArmies = 0;

		cout << "\nArmies after placing randomly - " << *(*players)[i].getName() << ":" << endl;
		for (int j = 0; j < (*players)[i].getCountries()->size(); j++) {
			cout << (j + 1) << ": " << (*(*(*players)[i].getCountries())[j]->getCountryName()) << " (armies: " << (*(*(*players)[i].getCountries())[j]->getCountryNumberArmies()) << ")" << endl;
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
			(*players)[i].reinforce();
			(*players)[i].attack();
			(*players)[i].fortify();

			ownsAllCountries = true;

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

void GameEngine::runTournament()
{
	cout << "MY TOUNRMANET";
}

MapLoader* GameEngine::LoadLoader(Map* map, string* mapPath)
{
	// Determine if it is a conquest map or not. If it is conquest map, open using the map adapter
	ifstream mapFile(*mapPath);
	string line;
	bool conquestMap = false;
	while (getline(mapFile, line))
	{
		if (line == "[Territories]")
			conquestMap = true;
	}
	mapFile.close();

	MapLoader* loader;
	if (conquestMap)
		loader = new MapAdapter();
	else
		loader = new MapLoader();

	return loader;
}

int GameEngine::choosingNumOfMaps()
{
	cout << "Choose the number of maps between 1 to 5:" << endl;
	cout << "> ";
	int numOfMaps;
	bool valid = false;
	cin >> numOfMaps;
	while(!valid){
		if (numOfMaps > 0 && numOfMaps <= 5) {
			valid = true;
		}
		else {
			cout << "the number you entered isn't valid! try again Balez" << endl;
			cin >> numOfMaps;
		}
	}
	return numOfMaps;
}

void GameEngine::choosingNumOfPlayers()
{
	cout << "Choose the number of Cumputer Players between 2 to 4:" << endl;
	cout << "> ";
	bool valid = false;
	int numCpuPlayers;
	cin >> numCpuPlayers;
	while (!valid) {
		if (numCpuPlayers > 1 && numCpuPlayers <= 4) {
			*numOfPlayers = numCpuPlayers;
			valid = true;
		}
		else {
			cout << "the number you entered isn't valid! try again Balez" << endl;
			cin >> numCpuPlayers;
		}
	}
}

void GameEngine::selectingMaps(int& mapsNum)
{
	string path("maps/");
	string ext(".map");
	vector<string> availableMaps;

	for (auto& p : fs::recursive_directory_iterator(path))
	{
		if (p.path().extension() == ext){
			availableMaps.push_back(p.path().stem().string());
			remainingMaps.push_back(p.path().stem().string());
		}
	}
	while(mapsNum != 0){
		cout << "Please select maps from the following list:" << endl;
		for (int i = 0; i < remainingMaps.size(); i++)
		{
			cout << (i + 1) << ": " << remainingMaps[i] << endl;
		}
		
		// checking USER'S input
		int n;
		cin >> n;
		bool valid = false;
		while (!valid) {
			if (n > 0 || n <= remainingMaps.size()) {
				valid = true;
			}
			else {
				cout << "Please choose a valid number" << endl;
				cin >> n;
			}
		}
	
		mapPath = new string(path + remainingMaps[n - 1] + ext);
		cout << "You have chosen " << *mapPath << endl;

		map = new Map();
		MapLoader* loader = LoadLoader(map, mapPath);// LoadLoader will load the correct map between domination and conquest map types
		loader->LoadMap(*map, *mapPath);
		bool validMap = map->ConnectedGraph(); // To check if the map is a connected graph
		while (!validMap) {
			cout << "Please choose another map" << endl;
			for (int i = 0; i < remainingMaps.size(); i++)
			{
				cout << (i + 1) << ": " << remainingMaps[i] << endl;
			}
			cin >> n;

			// checking USER'S input
			int n;
			cin >> n;
			bool valid = false;
			while (!valid) {
				if (n > 0 || n <= remainingMaps.size()) {
					valid = true;
				}
				else {
					cout << "Please choose a valid number" << endl;
					cin >> n;
				}
			}

			*mapPath = path + remainingMaps[n - 1] + ext;
			cout << "You have chosen " << *mapPath << endl;
			delete map;
			map = new Map();
			loader = LoadLoader(map, mapPath);// LoadLoader will load the correct map between domination and conquest map types
			loader->LoadMap(*map, *mapPath);
			validMap = map->ConnectedGraph(); // To check if the map is a connected graph
		}
		selectedMaps.push_back(remainingMaps[n - 1]); // adding map
		remainingMaps.erase(remainingMaps.begin() + n - 1); // removing map from the options
		mapsNum -= 1;
		delete loader;
		if(mapsNum != 0)
		cout << "You still have " << mapsNum << "to choose ." << endl; // TO BE MOVED TO ANOTHER PLACE
	}
}

void GameEngine::choosingNumOfMaxTurns()
{
	cout << "Choose the  maximum number of turns for each game between 10 to 50:" << endl;
	cout << "> ";
	int numOfTurns;
	bool valid = false;
	cin >> numOfTurns;
	while (!valid) {
		if (numOfTurns > 9 && numOfTurns <= 50) {
			*numOfMaxTurns = numOfTurns;
			valid = true;
		}
		else {
			cout << "the number you entered isn't valid! try again Balez" << endl;
			cout << "> ";
			cin >> numOfTurns;
		}
	}
}

void GameEngine::choosingNumOfGames()
{
	cout << "Choose the number games to be played on each map 1 to 5:" << endl;
	cout << "> ";
	int gameNum;
	bool valid = false;
	cin >> gameNum;
	while (!valid) {
		if (gameNum > 0 && gameNum <= 5) {
			*numOfGames = gameNum;
			valid = true;
		}
		else {
			cout << "the number you entered isn't valid! try again Balez" << endl;
			cout << "> ";
			cin >> gameNum;
		}
	}
}

void GameEngine::startupCpu(){
	randomizeOrder();
	cout << "The order of the play will be: " << endl;
	for (int i = 0; i < *numOfPlayers; i++) {
		cout << (i + 1) << ". " << *((*players)[i].getName()) << endl;
	}
	cout << endl;
	assignCountries();
	assignArmies();
}

void GameEngine::runGameCpu()
{
	string winner = "draw";
	int numTurn = *numOfMaxTurns;
	int count = 0;
	while (numTurn = !0) {
		bool finished = false;
		for (int i = 0; i < (*players).size(); i++) {
			bool ownsAllCountries = true;
			(*players)[i].reinforce();
			(*players)[i].attack();
			(*players)[i].fortify();

			ownsAllCountries = true;

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
			numTurn--;
	}
	cout << winner << " owns all the countries and wins the game!" << endl;
	winners.push_back(winner);
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

void GameEngineDriver::runTournamentStart()
{
	GameEngine g(true);
}

void GameEngine::run1vs1() {
	string winner;
	while (true) {
		bool finished = false;
		for (int i = 0; i < (*players).size(); i++) {
			bool ownsAllCountries = true;
			
			(*players)[i].executeStrategy();

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

GameEngine* GameEngineDriver::runPlayerVsCpu() {
	static GameEngine* g = new GameEngine(2);
	vector<PlayerObserver*> playerObservers;
	for (int i = 0; i < *(g->getNumOfPlayers()); i++) {
		playerObservers.push_back(new PlayerObserver(&(*(g)->getPlayers())[i]));
	}
	int numOfPlayers = *g->getNumOfPlayers();
	cout << numOfPlayers << " players have been created:" << endl;
	for (int i = 0; i < numOfPlayers; i++) {
		cout << (i + 1) << ". " << (*(*g->getPlayers())[i].getName()) << endl;
	}

	list<Card> deckCards = g->getDeck()->getAllCards();
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
	g->startup();
	g->run1vs1();

	return g;
}

GameEngine* GameEngineDriver::runModeSelection()
{
	cout << "Please select a game mode !" << endl;
	cout << "1: single game mode " << endl;
	cout << "2: tournament mode " << endl;
	bool validInput = false;
	int choice = 1;
	while (!validInput)
	{
		try
		{
			cin >> choice;
			if (choice == 1) {
				runGameStart();
				validInput = true;
			}
			else if (choice == 2) {
				runTournamentStart();
				validInput = true;
			}
			else
				throw choice;
		}
		catch (int error)
		{
			cout << "error! ...try Again" << endl;
		}
	}

	return nullptr;
}
