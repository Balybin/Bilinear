#pragma once
#include <vector>
using namespace std;
class Grid
{
public:
	vector<double> X, Y;
	int n, m;
	int calculatePosistion(int i, int j);
	void inputGrid();
};