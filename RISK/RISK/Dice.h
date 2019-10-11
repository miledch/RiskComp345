#pragma once
#include <vector>
using namespace std;
class Dice_Rolling_Facility
{
public:
	Dice_Rolling_Facility();
	~Dice_Rolling_Facility();

	//int* roll();
	vector<int> roll();
	vector<int> get_percentage();

	int* face; // array to keep count of number of times that each side was rolled
	int* count; // the total number of dice that was rolled for this facility
};

class DiceDriver
{
public:
	static void run();
};

