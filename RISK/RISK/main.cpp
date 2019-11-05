#include <iostream>
#include "Dice.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "GameEngine.h"

int main()
{


	PlayerDriver::runFortification();
	PlayerDriver::runReinforcement();
	GameEngine g;
	g.randomizeOrder();
	g.assignCountries();
	g.assignArmies();
	PlayerDriver::runAttackPhase();


	return 0;
}