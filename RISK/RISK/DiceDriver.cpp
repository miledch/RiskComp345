#include <iostream>
#include "Dice.h"

void DiceDriver::run() {
	Dice_Rolling_Facility dice1; // Create two facilities with defalut constructor
	Dice_Rolling_Facility dice2;

	vector<int> container; // This will be used retain the returned values of rolled dice

	cout << "Using Dice Rolling Facility 1:\n"; // Using the first object
	container = dice1.roll();
	cout << "You have rolled:\n";
	for (int i = 0; i < container.size(); i++) { // Print the values that were rolled
		cout << container[i] << "\n";
	}
	cout << "Percentages of numbers rolled for facility 1:\n";
	vector<int> dice1p = dice1.get_percentage(); // return the percentage of the numbers that each side was rolled so far
	for (int i = 0; i < dice1p.size(); i++) {
		cout << (i + 1) << ": " << dice1p[i] << "%\n";
	}

	cout << "\nUsing Dice Rolling Facility 2:\n"; // Using the second facility now
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

	cout << "\nUsing Dice Rolling Facility 1 again:\n"; // Using the first facility again
	container = dice1.roll();
	cout << "You have rolled:\n";
	for (int i = 0; i < container.size(); i++) {
		cout << container[i] << "\n";
	}
	cout << "Current percentages of numbers rolled for facility 1:\n";
	dice1p = dice1.get_percentage(); // Print the percentage of the first facility, which takes into account the numbers rolled the first time also
	for (int i = 0; i < dice1p.size(); i++) {
		cout << (i + 1) << ": " << dice1p[i] << "%\n";
	}

	int input = 1;
	while (input == 1) { // Keep rolling how many times you want to see if the numbers rolled have an equal share
		cout << "\nDo you want to roll dice 1 again?\n";
		cout << "1: Yes\n";
		cout << "2: No\n";
		cin >> input;
		if (input == 1) {
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
	}

	cout << "End of Dice Driver\n";

}