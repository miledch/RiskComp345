#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Player;

class GameObserver {
public:
	~GameObserver();
	virtual void Update() = 0;
protected:
	GameObserver();

};

class Subject {
public:
	virtual void Attach(GameObserver* o);
	virtual void Detach(GameObserver* o);
	virtual void Notify();
	Subject();
	~Subject();
protected:
	vector<GameObserver*>* observers;
};

class PlayerObserver : public GameObserver {
public:
	PlayerObserver(Player* p);
	~PlayerObserver();
	void Update();
private:
	Player* player;
};



