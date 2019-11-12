#include <iostream>
#include <vector>
#include "Player.h"
#include "Map.h"
using namespace std;

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
private:
	vector<GameObserver*>* observers;
};



