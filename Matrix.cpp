#include "Matrix.h"

void Matrix::make(GlobalMatrix &A)
{
	grid.inputGrid();
	profileDefining();
	matrixFilling();
	firstBoundaryConditions();
	A.di = this->di;
	A.ggl = al;
	A.ggu = au;
	A.ig = ia;
	A.jg = ja;
	A.n = this->n;
	A.F.V = f;
	A.normF = sqrt(A.F*A.F);
}

void Matrix::firstBoundaryConditions()
{
	int gridn = grid.n, gridm = grid.m;
	for (int i = 0; i < gridn; ++i)
	{//для нижней границы
		int k = grid.calculatePosistion(i, 0);
		for (int j = 0; j < n; ++j)
		{
			setEl_BC(k, j, 0);
		}
		setEl_BC(k, k, 1);
		f[k] = U(grid.X[k], grid.Y[0]);
	}
	for (int j = 0; j < gridm; ++j)
	{//для правой границы
		int k = grid.calculatePosistion(gridn - 1, j);
		for (int i = 0; i < n; ++i)
		{
			setEl_BC(k, i, 0);
		}
		setEl_BC(k, k, 1);
		f[k] = U(grid.X[gridn - 1], grid.Y[j]);
	}
	for (int i = 0; i < gridn; ++i)
	{//для верхней границы
		int k = grid.calculatePosistion(i, gridm-1);
		for (int j = 0; j < n; ++j)
		{
			setEl_BC(k, j, 0);
		}
		setEl_BC(k, k, 1);
		f[k] = U(grid.X[i], grid.Y[gridm-1]);
	}
	for (int j = 0; j < gridm; ++j)
	{//для левой границы, надеюсь, я ничего не перепутал
		int k = grid.calculatePosistion(0, j);
		for (int i = 0; i < n; ++i)
		{
			setEl_BC(k, i, 0);
		}
		setEl_BC(k, k, 1);
		f[k] = U(grid.X[0], grid.Y[j]);
	}
}
int Matrix::setEl_BC(int i, int j, double El)
{
	if (i == j)
	{
		di[i] = El;
		return 0;
	}
	if (i > j)
	{
		int i0 = ia[i];
		int i1 = ia[i + 1];
		for (int k = i0; k<i1; k++)
			if (ja[k] == j)
			{
				al[k] = El;
				return 0;
			}
		return -1;
	}
	else
	{
		swap(i, j);
		int i0 = ia[i];
		int i1 = ia[i + 1];
		for (int k = i0; k<i1; k++)
			if (ja[k] == j)
			{
				au[k] = El;
				return 0;
			}
		return -1;
	}
}
int Matrix::setEl(int i, int j, double El)
{
	if (i == j)
	{
		di[i] += El;
		return 0;
	}
	//if (j > i)	swap(i, j);//т.к. матрица симметрична
	if(i > j)
	{
		int i0 = ia[i];
		int i1 = ia[i+1];
		for(int k=i0; k<i1; k++)
			if (ja[k] == j)
			{
				al[k] += El;
				return 0;
			}
		return -1;
	}
	/*else
	{
	int k = ia[j], n = ia[j + 1] - ia[j];
	while (k < n && ja[k] != i)
	{
	k++;
	}
	if (ja[k] == i)
	{
	au[k] += El;
	return 0;
	}
	else
	{
	return -1;
	}
	}*/
}
void Matrix::matrixFilling()
{
	f.resize(n);
	for (int i = 0; i < n; i++)
		f[i] = 0;
	int index[4];
	double f1[4];
	int n = grid.n - 1, m = grid.m - 1;
	for (int j = 0; j < m; ++j) //по конечным элементам
	{
		for (int i = 0; i < n; ++i)
		{
			index[0] = grid.calculatePosistion(i, j);
			index[1] = grid.calculatePosistion(i + 1, j);
			index[2] = grid.calculatePosistion(i, j + 1);
			index[3] = grid.calculatePosistion(i + 1, j + 1);
			f1[0] = F(grid.X[i], grid.Y[j]);
			f1[1] = F(grid.X[i + 1], grid.Y[j]);
			f1[2] = F(grid.X[i], grid.Y[j + 1]);
			f1[3] = F(grid.X[i + 1], grid.Y[j + 1]);
			double Hx = grid.X[i + 1] - grid.X[i];
			double Hy = grid.Y[j + 1] - grid.Y[j];
			for (int i1 = 0; i1 < 4; i1++)
			{
				for (int j1 = 0; j1 < 4; j1++)
				{
					LocA[i1][j1] = Gmatrix(Hx, Hy, i1, j1) + Mmatrix(Hx, Hy, i1, j1);
				}
				LocB[i1] = Fvector(Hx, Hy, i1, f1);
			}

			for (int i1 = 0; i1 < 4; i1++)
			{
				for (int j1 = 0; j1 < 4; j1++)
					setEl(index[i1], index[j1], LocA[i1][j1]);
				f[index[i1]] += LocB[i1];
			}

		}
	}
	au = al;
}

void Matrix::profileDefining()
{
	n = grid.n * grid.m;
	int k = 0;
	listOfAdjacency.fillingList(grid);
	ia.reserve(n + 1);
	ja.reserve(4 * n);
	ia.push_back(0);
	di.reserve(n);
	al.reserve(4 * n);
	for (int i = 0; i < n; i++)
	{
		di.push_back(0);
		for (int j = 0; j < listOfAdjacency.list[i].size(); j++)
		{
			ja.push_back(listOfAdjacency.list[i][j]);
			al.push_back(0);
			au.push_back(0);
			k++;
		}
		ia.push_back(k);
	}
}