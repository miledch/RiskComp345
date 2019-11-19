#pragma once
#include <iostream>

using namespace std;
class Player;
class Strategy {
public:
	virtual void execute(Player *p) = 0;
};

class HumanPlayer : public Strategy {
public:
	void execute(Player* p);
};

class AggressivePlayer : public Strategy {
public:
	void execute(Player* p);
};

class BenevolentPlayer : public Strategy {
public:
	void execute(Player* p);
};