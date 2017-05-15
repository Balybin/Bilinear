#include "Grid.h"
#include <fstream>
#include <iostream>


int Grid::calculatePosistion(int i, int j)
{
	if (i >= n || j >= m || i < 0 || j < 0 )
		return -1;
	int k = j * n + i;
	if (k >= 0)
		return k;
	else
		return -1;
}
void Grid::inputGrid()
{
	ifstream file("grid.txt");
	int count, ibuf;
	double buf;
	vector<double> toBorder, toMinStep, toDecompactionCoef;
	vector<int> Direction;
	file >> buf;
	toBorder.push_back(buf);
	file >> count;
	for (int i = 1; i <= count; i++)
	{
		file >> buf;
		toBorder.push_back(buf);
	}
	for (int i = 0; i < count; i++)
	{
		file >> buf;
		toMinStep.push_back(buf);
	}
	for (int i = 0; i < count; i++)
	{
		file >> buf;
		toDecompactionCoef.push_back(buf);
	}
	X.push_back(toBorder[0]);
	n = 1;
	for (int i = 0; i < count; i++)
	{
		buf = toMinStep[i];
		while (X[n - 1] + buf <= toBorder[i + 1])
		{
			X.push_back(X[n - 1] + buf);
			n++;
			buf *= toDecompactionCoef[i];
		}
		X.push_back(toBorder[i + 1]); n++;
	}
	//теперь для У
	toBorder.resize(0);
	toDecompactionCoef.resize(0);
	toMinStep.resize(0);
	file >> buf;
	toBorder.push_back(buf);
	file >> count;
	for (int i = 1; i <= count; i++)
	{
		file >> buf;
		toBorder.push_back(buf);
	}
	for (int i = 0; i < count; i++)
	{
		file >> buf;
		toMinStep.push_back(buf);
	}
	for (int i = 0; i < count; i++)
	{
		file >> buf;
		toDecompactionCoef.push_back(buf);
	}
	/*for (int i = 0; i < count; i++)
	{ Вот это потом можно сделать, чтобы было как в тэльме, заодно можно так же добавить удвоение сетки, но надо ли..?
	file >> ibuf;
	Direction.push_back(ibuf);
	}*/
	Y.push_back(toBorder[0]);
	m = 1;
	for (int i = 0; i < count; i++)
	{
		buf = toMinStep[i];
		while (Y[m - 1] + buf <= toBorder[i + 1])
		{
			Y.push_back(Y[m - 1] + buf);
			m++;
			buf *= toDecompactionCoef[i];
		}
		Y.push_back(toBorder[i + 1]); m++;
	}
}
// void Grid::inputGrid()
// {
	// ifstream file("grid.txt");
	// int count, ibuf;
	// double buf;
	// vector<double> toBorder, toMinStep, toDecompactionCoef;
	// vector<int> Direction;
	// file >> buf;
	// toBorder.push_back(buf);
	// file >> count;
	// for (int i = 1; i <= count; i++)
	// {
		// file >> buf;
		// toBorder.push_back(buf);
	// }
	// for (int i = 0; i < count; i++)
	// {
		// file >> buf;
		// toMinStep.push_back(buf);
	// }
	// for (int i = 0; i < count; i++)
	// {
		// file >> buf;
		// toDecompactionCoef.push_back(buf);
	// }
	// /*for (int i = 0; i < count; i++)
	// { Вот это потом можно сделать, чтобы было как в тэльме, заодно можно так же добавить удвоение сетки, но надо ли..?
	// file >> ibuf;
	// Direction.push_back(ibuf);
	// }*/
	// X.push_back(toBorder[0]);
	// n = 1;
	// for (int i = 0; i < count; i++)
	// {
		// buf = toMinStep[i];
		// while (X[n - 1] < toBorder[i + 1])
		// {
			// X.push_back(X[n - 1] + buf);
			// n++;
			// buf *= toDecompactionCoef[i];
		// }
		// X[n - 1] = toBorder[i + 1];
	// }
	// //теперь для У
	// toBorder.resize(0);
	// toDecompactionCoef.resize(0);
	// toMinStep.resize(0);
	// file >> buf;
	// toBorder.push_back(buf);
	// file >> count;
	// for (int i = 1; i <= count; i++)
	// {
		// file >> buf;
		// toBorder.push_back(buf);
	// }
	// for (int i = 0; i < count; i++)
	// {
		// file >> buf;
		// toMinStep.push_back(buf);
	// }
	// for (int i = 0; i < count; i++)
	// {
		// file >> buf;
		// toDecompactionCoef.push_back(buf);
	// }
	// /*for (int i = 0; i < count; i++)
	// { Вот это потом можно сделать, чтобы было как в тэльме, заодно можно так же добавить удвоение сетки, но надо ли..?
	// file >> ibuf;
	// Direction.push_back(ibuf);
	// }*/
	// Y.push_back(toBorder[0]);
	// m = 1;
	// for (int i = 0; i < count; i++)
	// {
		// buf = toMinStep[i];
		// while (Y[m - 1] < toBorder[i + 1])
		// {
			// Y.push_back(Y[m - 1] + buf);
			// m++;
			// buf *= toDecompactionCoef[i];
		// }
		// Y[m - 1] = toBorder[i + 1];
	// }
// }

//void Grid::inputGrid()
//{
//	ifstream input("inf2tr.dat");
//
//	input.close();
//
//	input.open();
//
//	input.close();
//}