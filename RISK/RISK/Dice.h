#pragma once
#include <vector>
using namespace std;
class Dice_Rolling_Facility
{
public:
	Dice_Rolling_Facility();
	~Dice_Rolling_Facility();

	vector<int> roll(); // Method that returns a container to store the numbers rolled from dice
	vector<int> get_percentage(); // Returns container that the percentage that each number was rolled

	int* getCount() const;
	void setCount(int);
	int* getFace() const;

private:
	int* face; // array to keep count of number of times that each side was rolled
	int* count; // the total number of dice that was rolled for this facility
};

class DiceDriver
{
public:
	static void run(); // Basically the driver method
};

