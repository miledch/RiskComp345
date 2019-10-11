#include <iostream>
using namespace std;
#include "Dice.h"
#include "Map.h"
#include "Player.h"

int main()
{
	cout << "Hello team " << endl;
	MapDriver::RunMapDriver();
	MapLoaderDriver::RunMapLoaderDriver();
	DiceDriver::run();
	Player::run();
	// insert Card::run() here
	return 0;
}