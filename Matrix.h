#pragma once
#include "ListOfAdjacency.h"
#include "Grid.h"
#include "GlobalMatrix.h"

using namespace std;

extern double F(double x, double y);
extern double U(double x, double y);
extern double Fvector(double Hx, double Hy, int i, double *f);
extern double Mmatrix(double Hx, double Hy, int i, int j);
extern double Gmatrix(double Hx, double Hy, int i, int j);

#pragma once
class Matrix
{
public:
	int n;
	vector<double> di, al, au, f;
	vector<int> ia, ja;
	ListOfAdjacency listOfAdjacency;
	Grid grid;
	double LocA[4][4];
	double LocB[4];
	int setEl(int i, int j, double El);
	void matrixFilling();
	void profileDefining();
	void make(GlobalMatrix &A);
	void firstBoundaryConditions();
	int setEl_BC(int i, int j, double El);
};