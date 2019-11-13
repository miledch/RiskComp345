#include "GameObservers.h"
#include <algorithm>

Subject::Subject() {
	observers = new vector<GameObserver*>;
}
Subject::~Subject() {
	delete observers;
}
void Subject::Attach(GameObserver* o) {
	observers->push_back(o);
};
void Subject::Detach(GameObserver* o) {
	observers->erase(remove(observers->begin(), observers->end(), o), observers->end());
};
void Subject::Notify() {
	vector<GameObserver*>::iterator i = observers->begin();
	for (; i != observers->end(); ++i)
		(*i)->Update();
};

GameObserver::GameObserver() {
};
GameObserver::~GameObserver() {
};
