#include "PlayerStrategies.h"
#include "Player.h"

void HumanPlayer::execute(Player* p) {
	p->reinforce();
	p->attack();
	p->fortify();
}

void AggressivePlayer::execute(Player* p) {
	p->reinforce();
	p->attack();
	p->fortify();
}

void BenevolentPlayer::execute(Player* p) {
	p->reinforce();
	p->fortify();
}
