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
		face[i] = 0; // Initialize all the slots to zero since we haven't rolled the die yet
	}
	count = new int(0);
}

Dice_Rolling_Facility::Dice_Rolling_Facility(const Dice_Rolling_Facility& dice2)
{
	face = new int[6];
	for (int i = 0; i < 6; i++) {
		face[i] = dice2.face[i];
	}
	count = new int(*dice2.count);
}

vector<int> Dice_Rolling_Facility::roll() {
	cout << "How many dice do you want to roll (1-3)?" << endl;
	int number;
	cin >> number;
	while (number < 1 || number > 3) { // validate the number entered by the user since we can only roll 1, 2, or 3 times
		cout << "Please choose a number between 1 and 3";
		cin >> number;
	}

	vector<int> container(number); // This is the vector that we are going to return that will contain the nummbers
	srand(time(NULL));
	for (int i = 0; i < number; i++) {
		container[i] = rand() % 6 + 1; // Generate the random numbers (1-3 times)
		(*this).face[container[i]-1]++; // keep count of the number that was rolled
		(*(*this).count)++;
	}

	sort(container.begin(), container.end(), greater<int>()); //sort from big to small
	
	return container; // returns the sorted vector
}

vector<int> Dice_Rolling_Facility::get_percentage() {
	vector<int> percentage(6);

	for (int i = 0; i < percentage.size(); i++) {
		percentage[i] = ((*this).face[i] * 100) / (*(*this).count);
	}

	// Return a vector that shows the percentage of times that each number was rolled
	return percentage;
}

int Dice_Rolling_Facility::getCount() const {
	return *count; // returns (copied) value, not pointer or reference
}

const int* Dice_Rolling_Facility::getFace() const {
	return face; // returns a pointer to the actual array, but it is const so that we can't change the values
}


Dice_Rolling_Facility::~Dice_Rolling_Facility()
{
	delete this->face;
	delete this->count;
	face = NULL;
	count = NULL;
}

Dice_Rolling_Facility& Dice_Rolling_Facility::operator=(const Dice_Rolling_Facility& rhs)
{
	if (this != &rhs) {
		for (int i = 0; i < 6; i++) {
			face[i] = rhs.face[i];
		}

		*count = *(rhs.count);
	}
	return *this;
}
