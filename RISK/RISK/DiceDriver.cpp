#include <iostream>
#include "Dice.h"

void DiceDriver::run() {
	Dice_Rolling_Facility dice1;
	Dice_Rolling_Facility dice2;

	vector<int> container;

	cout << "Using Dice Rolling Facility 1:\n";
	container = dice1.roll();
	cout << "You have rolled:\n";
	for (int i = 0; i < container.size(); i++) {
		cout << container[i] << "\n";
	}
	cout << "Percentages of numbers rolled for facility 1:\n";
	vector<int> dice1p = dice1.get_percentage();
	for (int i = 0; i < dice1p.size(); i++) {
		cout << (i + 1) << ": " << dice1p[i] << "%\n";
	}

	cout << "\nUsing Dice Rolling Facility 2:\n";
	container = dice2.roll();
	cout << "You have rolled:\n";
	for (int i = 0; i < container.size(); i++) {
		cout << container[i] << "\n";
	}
	cout << "Percentages of numbers rolled for facility 2:\n";
	vector<int> dice2p = dice2.get_percentage();
	for (int i = 0; i < dice2p.size(); i++) {
		cout << (i + 1) << ": " << dice2p[i] << "%\n";
	}

	cout << "\nUsing Dice Rolling Facility 1 again:\n";
	container = dice1.roll();
	cout << "You have rolled:\n";
	for (int i = 0; i < container.size(); i++) {
		cout << container[i] << "\n";
	}
	cout << "Current percentages of numbers rolled for facility 1:\n";
	dice1p = dice1.get_percentage();
	for (int i = 0; i < dice1p.size(); i++) {
		cout << (i + 1) << ": " << dice1p[i] << "%\n";
	}

	char input;
	while (true) {
		cout << "\nDo you want to roll dice 1 again? (y/n)\n";
		cin >> input;
		if (input == 'y') {
			cout << "\nUsing Dice Rolling Facility 1 again:\n";
			container = dice1.roll();
			cout << "You have rolled:\n";
			for (int i = 0; i < container.size(); i++) {
				cout << container[i] << "\n";
			}
			cout << "Current percentages of numbers rolled for facility 1:\n";
			dice1p = dice1.get_percentage();
			for (int i = 0; i < dice1p.size(); i++) {
				cout << (i + 1) << ": " << dice1p[i] << "%\n";
			}
		}
		if (input != 'y')
			break;
	}

}