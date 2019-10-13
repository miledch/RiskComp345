#include <iostream>
using namespace std;
#include "Dice.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"

int main()
{
	MapDriver::RunMapDriver();
	cout << "\n";
	MapLoaderDriver::RunMapLoaderDriver();
	cout << "\n";
	DiceDriver::run();
	cout << "\n";
	PlayerDriver::run();
	cout << "\n";
	CardDriver::run();
	return 0;
}