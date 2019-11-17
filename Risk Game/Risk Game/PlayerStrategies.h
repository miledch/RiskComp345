#pragma once
#include <iostream>
#include "GameEngine.h"
#include "Player.h"

using namespace std;

class Strategy {
public:
	virtual void execute() = 0;
};

class HumanPlayer : public Strategy {
public:
	void execute();
};

class AggressivePlayer : public Strategy {
public:
	void execute();
};

class BenevolentPlayer : public Strategy {
public:
	void execute();
};