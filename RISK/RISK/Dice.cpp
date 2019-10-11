#include <iostream>
#include "Dice.h"
#include <ctime>
#include <algorithm>
#include <vector>
using namespace std;

Dice_Rolling_Facility::Dice_Rolling_Facility()
{
	face = new int[6]; // face is to keep count of the number that was rolled
	for (int i = 0; i < 6; i++) {
		face[i] = 0;
	}
	count = new int(0);
}

vector<int> Dice_Rolling_Facility::roll() {
	cout << "How many dice do you want to roll (1-3)?" << endl;
	int number;
	cin >> number;
	while (number < 1 || number > 3) { // validate the number entered by the user
		cout << "Please choose a number between 1 and 3";
		cin >> number;
	}

	//static int* container = new int[number]; // it's static so that we could return the address of array
	vector<int> container(number);
	srand(time(NULL));
	for (int i = 0; i < number; i++) {
		container[i] = rand() % 6 + 1; // Generate the random numbers (1-3 times)
		(*this).face[container[i]-1]++; // keep count of the number that was rolled
		(*(*this).count)++;
	}

	sort(container.begin(), container.end(), greater<int>()); //sort from big to small
	
	return container;
}

vector<int> Dice_Rolling_Facility::get_percentage() {
	vector<int> percentage(6);

	for (int i = 0; i < percentage.size(); i++) {
		percentage[i] = ((*this).face[i] * 100) / (*(*this).count);
	}

	return percentage;
}


Dice_Rolling_Facility::~Dice_Rolling_Facility()
{
	delete this->face; // How to properly delete 'face'? (it's an array)
	delete this->count;
}
