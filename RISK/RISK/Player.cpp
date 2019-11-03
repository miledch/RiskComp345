#include "Player.h"

// Default constructor
Player::Player() 
{
	countries = new vector<Country>();
	dice = new Dice_Rolling_Facility();
	h = new Hand(*(new Deck(0)));
}

// Parameterized constructor
Player::Player(Map* map, vector<Country>* c, Dice_Rolling_Facility* d, Hand* h)
{
	this->map = map;
	this->countries = c;
	this->dice = d;
	this->h = h;
}

Player::Player(const Player& p2)
{
	this->map = new Map(*p2.map);
	this->countries = new vector<Country>(*p2.countries);
	this->dice = new Dice_Rolling_Facility(*p2.dice);
	this->h = new Hand(*p2.h);
}

Player& Player::operator=(const Player& rhs)
{
	if (this != &rhs) 
	{
		*(this->map) = *(rhs.map);
		*(this->countries) = *(rhs.countries);
		*(this->dice) = *(rhs.dice);
		*(this->h) = *(rhs.h);
	}
	return *this;
}

// Destructor
Player::~Player() 
{	
	for (vector<Country>::iterator it = countries->begin(); it != countries->end(); ++it)
	{
		it->deleteCountry();
	}
	//delete map;
	//map = NULL;
	delete h;
	h = NULL;
	delete dice;
	dice =NULL;

}

// Get player's dice
Dice_Rolling_Facility* Player::getDice() 
{
	return this->dice;
}

// Get player's hand of cards
Hand* Player::getHand() 
{
	return this->h;
}

// Get player's vector of countries
vector<Country>* Player::getCountries() const
{
	return this->countries;
}

// Change the set of player's countries
void Player::changeCountries(vector<Country>* c)
{
	this->countries = c;
}

// Change the hand of cards
void Player::changeHand(Hand* hd) 
{
	this->h = hd;
}

// Print player's countries
void Player::printCountries() 
{
	if (countries->empty() == true) 
	{
		cout << "This player has no countries!\n";
	}
	else 
	{
		for (int i = 0; i < countries->size(); i++) 
		{
			Country c = countries->at(i);
			c.printCountry();
			cout << endl;
		}
	}
}

void Player::reinforce() 
{
	cout << "I'm reinforcing!\n";
}

void Player::attack()
{
	int playerDecision = 0;
	while (playerDecision != 2)
	{
		cout << "\nDo you want to attack adjacent territories ?" << endl;
		cout << "Press 1 for yes or 2 for no: ";
		cout << ">";
		cin >> playerDecision;
		if (playerDecision == 1)
			attackPhase();
	}
}

void Player::attackPhase()
{
	Country* attackCountry = NULL;
	Country* targetedCountry = NULL;

	int countrySelected;
	bool validSelection = false;
	vector<Country>::iterator it;
	//The player selects one of its countries to attack from, The attacking country must have at least 2 armies on it
	do
	{
		cout << "\nSelect which countries you want to attack from by entering the country ID" << endl << endl;

		for (it = countries->begin(); it != countries->end(); ++it)
		{
			if (*(it->getCountryNumberArmies()) >= 2)
			{
				cout << *it->getCountryID() << "\tCountry " << *it->getCountryName() << " has " << *it->getCountryNumberArmies() << " armies available" << endl;
			}
		}
		cout << ">";
		cin >> countrySelected;
		for (it = countries->begin(); it != countries->end(); ++it)
		{
			if (*it->getCountryNumberArmies() >= 2)
			{
				if (countrySelected == *it->getCountryID())
				{
					attackCountry = &(*it);
					validSelection = true;
				}
					
			}
		}
		if(!validSelection)
			cout << "Enter a valid country ID " << endl;
	} 
	while (!validSelection);

	//find the index of the countries list corresponding to our countrySelected;
	int index;
	for (it = countries->begin(); it != countries->end(); ++it)
	{
		if (*it->getCountryID() == countrySelected)
		{
			index = std::distance(countries->begin(), it);
			break;
		}
	}

	cout << "\nChoose a country to attack !" << endl;
	cout << "Neighboring countries of country " << countrySelected << " are:" << endl << endl;

	list<int>::iterator l_it;
	list<Country>::iterator countriesIt;
	vector<int> validEntryForAttack;
	for (l_it = attackCountry->getNeighbors()->begin(); l_it != attackCountry->getNeighbors()->end(); ++l_it)
	{
		for (countriesIt = map->getCountries()->begin(); countriesIt != map->getCountries()->end(); ++countriesIt)
		{
			if (*countriesIt->getCountryID() == *l_it)
			{
				cout << *countriesIt->getCountryID() << "\t" << *countriesIt->getCountryName() << " containing " << *countriesIt->getCountryNumberArmies() << " armies." << endl;
				validEntryForAttack.push_back(*countriesIt->getCountryID());
				break;
			}
		}
	}
	int attackSelection;
	validSelection = false;
	vector<int>::iterator vecInt_it;
	do
	{
		cout << ">";
		cin >> attackSelection;
		for (vecInt_it = validEntryForAttack.begin(); vecInt_it != validEntryForAttack.end(); vecInt_it++)
		{
			if (attackSelection == *vecInt_it)
			{
				validSelection = true;
			}
				
		}
		if (!validSelection)
		{
			cout << "Please enter a valid country ID" << endl;
			for (l_it = attackCountry->getNeighbors()->begin(); l_it != attackCountry->getNeighbors()->end(); ++l_it)
			{
				for (countriesIt = map->getCountries()->begin(); countriesIt != map->getCountries()->end(); ++countriesIt)
				{
					if (*countriesIt->getCountryID() == *l_it)
					{
						cout << *countriesIt->getCountryID() << "\t" << *countriesIt->getCountryName() << " containing " << *countriesIt->getCountryNumberArmies() << " armies." << endl;
						break;
					}
				}
			}
		}	
	} 
	while (!validSelection);

	// assign the pointer to the target country
	for (countriesIt = map->getCountries()->begin(); countriesIt != map->getCountries()->end(); ++countriesIt)
	{
		if (*countriesIt->getCountryID() == attackSelection)
		{
			targetedCountry = &(*countriesIt);
		}
	}

	// The attacker is allowed 1 to 3 dice, with the maximum number of dice being the number of armies on the attacking country, minus one.
	cout << "\nAttacker country " << *countries->at(index).getCountryID() << " " << *countries->at(index).getCountryName() <<
		" is owned by " << *countries->at(index).getCountryPlayerOwned() << endl;
	cout << "Please select your number of dice to roll for your attack!" << endl;
	int attackerNbrDice;
	validSelection = false;
	do
	{
		// for loop to display the dice options
		int maxDice;
		switch (*attackCountry->getCountryNumberArmies())
		{
		case 3:
			maxDice = 2;
			break;
		case 2:
			maxDice = 1;
			break;
		default:
			maxDice = 3;
			break;
		}
		for (size_t i = 1; i <= maxDice; i++)
		{
			cout << i << ": " << i << " dice" << endl;
		}
		cout << ">";
		cin >> attackerNbrDice;
		// for loop to check if the dice input is a valid selection
		for (size_t i = 1; i <= maxDice; i++)
		{
			if (attackerNbrDice == i)
			{
				validSelection = true;
				break;
			}	
		}
		if(!validSelection)
			cout << "Please enter a valid dice number" << endl;
	} 
	while (!validSelection);

	
	// The defender is allowed 1 to 2 dice, with the maximum number of dice being the number of armies on the defending country
	// if the defending country has 1 army, only 1 dice allowed. For 2 armies and +, then he is allowed 2 dice
	int defenderNbrDice;

	cout << "\nDefender country " << *targetedCountry->getCountryID() << " " << *targetedCountry->getCountryName() <<
		" is owned by " << *targetedCountry->getCountryPlayerOwned() << endl;
	if (*targetedCountry->getCountryNumberArmies() == 0)
	{
		cerr << "***This country has no armies***" << endl;
		cerr << "This is an error, not supposed to print this message";
		return;
	}
				
	cout << "Please select your number of dice to roll for your defense!" << endl;
	validSelection = false;
	do
	{
		// for loop to display the dice options
		int maxDice;
		switch (*targetedCountry->getCountryNumberArmies())
		{
		case 1:
			maxDice = 1;
			break;
		default:
			maxDice = 2;
			break;
		}
		for (size_t i = 1; i <= maxDice; i++)
		{
			cout << i << ": " << i << " dice" << endl;
		}
		cout << ">";
		cin >> defenderNbrDice;
		// for loop to check if the dice input is a valid selection
		for (size_t i = 1; i <= maxDice; i++)
		{
			if (defenderNbrDice == i)
			{
				validSelection = true;
				break;
			}
		}
		if (!validSelection)
			cout << "Please enter a valid dice number" << endl;
	} 
	while (!validSelection);


	// Attacker rolls his dices
	vector<int> attackerRoll = this->getDice()->roll(attackerNbrDice);
	// Defender rolls his dices
	vector<int> defenderRoll = this->getDice()->roll(defenderNbrDice);
	cout << endl;
	cout << *attackCountry->getCountryPlayerOwned() << " country " << *attackCountry->getCountryID()
		<< " " << *attackCountry->getCountryName() << " rolled ";
	for (vecInt_it = attackerRoll.begin(); vecInt_it != attackerRoll.end(); vecInt_it++)
	{
		cout << *vecInt_it << " ";
	}

	cout << "\n" << *targetedCountry->getCountryPlayerOwned() << " country " << *targetedCountry->getCountryID()
		<< " " << *targetedCountry->getCountryName() << " rolled ";
	for (vecInt_it = defenderRoll.begin(); vecInt_it != defenderRoll.end(); vecInt_it++)
	{
		cout << *vecInt_it << " ";
	}
	cout << endl;

	//Match up the highest attack die with the highest defender die, and match the second highest attack die with the second
	//highest defender die. If there is only one attack die, only match up the highest attack die with the defender die
	const int loopNbr = std::min(attackerNbrDice, defenderNbrDice);
	for (size_t i = 0; i < loopNbr; i++)
	{
		// because attackerRoll is in ascending order, the back() returns the highest roll
		int attack = attackerRoll.back();
		attackerRoll.pop_back();

		int defense = defenderRoll.back();
		if(defenderRoll.size() > 1)
			defenderRoll.pop_back();

		cout << "\nBecause " << *attackCountry->getCountryPlayerOwned() << " rolled " << attack << " and "
			<< *targetedCountry->getCountryPlayerOwned() << " rolled " << defense << endl;
		//Remove one of your opponent’s army from the defending territory if the attack die is higher to its corresponding defense die.
		if (attack > defense)
		{
			targetedCountry->setCountryNumberArmies(--(*targetedCountry->getCountryNumberArmies()));
			cout << "Country " << *targetedCountry->getCountryName() << " from " << *targetedCountry->getCountryPlayerOwned()
				<< " lost one army and is now at " << *targetedCountry->getCountryNumberArmies() << endl;
		}
		else // if dices are equal or defense > attack
		{
			attackCountry->setCountryNumberArmies(--(*attackCountry->getCountryNumberArmies()));
			cout << "Country " << *attackCountry->getCountryName() << " from " << *attackCountry->getCountryPlayerOwned()
				<< " lost one army and is now at " << *attackCountry->getCountryNumberArmies() << endl;
		}

		// check if the attack country ran out of armies
		if (*attackCountry->getCountryNumberArmies() == 0)
		{
			cout << "The aggressor " << *attackCountry->getCountryPlayerOwned() << " has been defeated and lost country "
				<< *attackCountry->getCountryName() << endl;
			// player removes his attack country from his list of countries using our index
			countries->erase(countries->begin() + index);
			// remove this country from the map
			for (countriesIt = map->getCountries()->begin(); countriesIt != map->getCountries()->end(); ++countriesIt)
			{
				if (*countriesIt->getCountryID() == *attackCountry->getCountryID())
				{
					countriesIt->setCountryPlayerOwned("NULL");
					countriesIt->setCountryNumberArmies(0);
					break;
				}
			}
		}
		else if (*targetedCountry->getCountryNumberArmies() == 0)
		{
			cout << "Targeted  " << *targetedCountry->getCountryPlayerOwned() << " has been defeated and lost country "
				<< *targetedCountry->getCountryName() << endl;
			// player now owns the targeted countries
			countries->push_back(*targetedCountry);
			// modify the map object
			for (countriesIt = map->getCountries()->begin(); countriesIt != map->getCountries()->end(); ++countriesIt)
			{
				if (*countriesIt->getCountryID() == attackSelection)
				{
					countriesIt->setCountryPlayerOwned(*attackCountry->getCountryPlayerOwned());
					// player must now decide how many armies to move to the new country
					int nbrArmies;
					validSelection = false;
					do
					{
						cout << "\nIn order to move armies to the conquered country, select a number between 1 and "
							<< (*attackCountry->getCountryNumberArmies() - 1) << endl;
						cout << ">";
						cin >> nbrArmies;
						if (nbrArmies > 1 && nbrArmies < *attackCountry->getCountryNumberArmies())
							validSelection = true;
						else
							cout << "\nPlease enter a valid number" << endl;
					} 
					while (!validSelection);

					countriesIt->setCountryNumberArmies(nbrArmies);
					break;
				}
			}
		}
	}

	attackCountry = nullptr;
	targetedCountry = nullptr;


}

void Player::fortify() 
{
	cout << "I'm fortifying!\n";
}

