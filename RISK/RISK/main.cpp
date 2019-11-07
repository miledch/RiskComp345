#include <iostream>
#include "Dice.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "GameEngine.h"

int main()
{

	//MapDriver::RunMapDriver(); // from assignment 1, to test graph an subgraph connected

	/*PlayerDriver::runFortification();
	PlayerDriver::runReinforcement();*/
	GameEngineDriver::runGameStart();
	/*g.randomizeOrder();
	g.assignCountries();
	g.assignArmies();
	g.runGame();
	PlayerDriver::runAttackPhase();*/


	return 0;
}