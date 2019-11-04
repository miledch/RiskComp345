#pragma once
#include <vector>
using namespace std;
class Dice_Rolling_Facility
{
public:
	Dice_Rolling_Facility();
	Dice_Rolling_Facility(const Dice_Rolling_Facility& dice2);
	~Dice_Rolling_Facility();
	Dice_Rolling_Facility& operator=(const Dice_Rolling_Facility& rhs);

	vector<int> roll(); // Method that returns a container to store the numbers rolled from dice
	vector<int> get_percentage(); // Returns container that the percentage that each number was rolled

	int getCount() const; // Returns copy of count
	const int* getFace() const; // Returns pointer to the face array but is const so we can't change values

private:
	int* face; // array to keep count of number of times that each side was rolled
	int* count; // the total number of dice that was rolled for this facility
};

class DiceDriver
{
public:
	static void run(); // Basically the driver method
};

