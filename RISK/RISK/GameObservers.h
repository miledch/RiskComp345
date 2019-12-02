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
	virtual void UpdatePhase() = 0; // Two separate functions since we are observing players 
								// at different times for different purposes
protected:
	GameObserver();

};

class Subject {
public:
	virtual void Attach(GameObserver* o);
	virtual void Detach(GameObserver* o);
	virtual void Notify(); // this function will be called in the attak method in Player class after a contry is occupied .
	virtual void NotifyPhase(); // This calls the UpdatePhase() functions on all its obervers (as opposed to Update())
	Subject();
	~Subject();
protected:
	vector<GameObserver*>* observers;
};

class PlayerObserver : public GameObserver {
public:
	PlayerObserver(Player* p);
	~PlayerObserver();
	void updateIWordPercentage();
	void Update();
	void UpdatePhase();
private:
	float iWorldPercentage;
	Player* player;
};



