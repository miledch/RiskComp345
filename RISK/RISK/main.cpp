#include <iostream>
using namespace std;
#include "Dice.h"
#include "Map.h"
#include "Player.h"

int main()
{
	MapDriver::RunMapDriver();
	cout << "\n";
	MapLoaderDriver::RunMapLoaderDriver();
	cout << "\n";
	DiceDriver::run();
	cout << "\n";
	Player::run();
	cout << "\n";
	// insert Card::run() here
	return 0;
}