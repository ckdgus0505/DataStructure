#include "sparse.h"

void smatrix::convert_to_smatrix(int n, int** mat)
{
	smatrix::n = n;
	smatrix::cnt = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cnt++;
		}
	}
	smatrix::list = new element[cnt];
	smatrix::cnt = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (mat[i][j] != 0)
			{
				element tmp;
				tmp.row = i;
				tmp.col = j;
				tmp.val = mat[i][j];
				smatrix::list[++cnt] = tmp;
			}
		}
	}
	element tmp;
	tmp.col = n;
	tmp.row = n;
	tmp.val = cnt;
	smatrix::list[0] = tmp;
}

void smatrix::ready()
{
	int numCols = this->list[0].col;
	int numTerms = this->list[0].val;
	this->rowTerms = new int[this->cnt];
	this->startPos = new int[this->cnt];

	// Compute rowTerms[i]
	for (int i = 0; i < numCols; i++)
	{
		this->rowTerms[i] = 0;
	}
	for (int i = 0; i <= numTerms; i++)
	{
		this->rowTerms[this->list[i].col]++;
	}
	// Compute startingPos[i]
	this->startPos[0] = 1;
	for (int i = 1; i < numCols; i++)
	{
		this->startPos[i] = this->startPos[i - 1] + this->rowTerms[i - 1];
	}

	for (int i = 1; i < cnt; i++)
	{
		this->startPos[i] = this->startPos[i - 1] + rowTerms[i - 1];
	}
}
void smatrix::fastTranspose(smatrix smat)
{
	smat.ready();
	this->list = new element[smat.cnt + 1];

	//smatrix::ready();
	int i, j;
	int numCols = smat.list[0].col;
	int numTerms = smat.list[0].val;
	this->list[0].col = numCols;
	this->list[0].row = numCols;
	this->list[0].val = numTerms;
	this->cnt = numTerms;
	this->n = numCols;

	for (i = 1; i <= numTerms; i++)
	{
		j = smat.startPos[smat.list[i].col]++;
		this->list[j].row = smat.list[i].col;
		this->list[j].col = smat.list[i].row;
		this->list[j].val = smat.list[i].val;
	}
}
void smatrix::fastAdd(smatrix  smatA, smatrix smatB)
{
	this->list = new element[smatA.cnt + smatB.cnt];
	this->n = smatA.n;
	this->cnt = 0;
	int iterA = 1;
	int iterB = 1;
	int i = 1;
	while (iterA <= smatA.cnt && iterB <= smatB.cnt)
	{
		if (smatA.list[iterA].row == smatB.list[iterB].row)
		{
			if (smatA.list[iterA].col == smatB.list[iterB].col)
			{
				this->list[i].row = smatA.list[iterA].row;
				this->list[i].col = smatA.list[iterA].col;
				this->list[i].val = smatA.list[iterA].val + smatB.list[iterB].val;
				iterA++;
				iterB++;
			}
			else if (smatA.list[iterA].col < smatB.list[iterB].col)
			{
				this->list[i].row = smatA.list[iterA].row;
				this->list[i].col = smatA.list[iterA].col;
				this->list[i].val = smatA.list[iterA].val;
				iterA++;
			}
			else if(smatA.list[iterA].col > smatB.list[iterB].col)
			{
				this->list[i].row = smatB.list[iterB].row;
				this->list[i].col = smatB.list[iterB].col;
				this->list[i].val = smatB.list[iterB].val;
				iterB++;
			}
		}
		else if (smatA.list[iterA].row < smatB.list[iterB].row)
		{
			this->list[i].row = smatA.list[iterA].row;
			this->list[i].col = smatA.list[iterA].col;
			this->list[i].val = smatA.list[iterA].val;
			iterA++;
		}
		else if(smatA.list[iterA].row > smatB.list[iterB].row)
		{
			this->list[i].row = smatB.list[iterB].row;
			this->list[i].col = smatB.list[iterB].col;
			this->list[i].val = smatB.list[iterB].val;
			iterB++;

		}
		this->cnt++;
		i++;
	}
	this->list[0].val = this->cnt;
	this->list[0].col = smatA.n;
	this->list[0].row = smatA.n;

}
void smatrix::fastMult(smatrix  smatA, smatrix smatB)
{
	smatrix smatBT;
	smatA.ready();
	smatBT.ready();
	smatBT.fastTranspose(smatB);
	this->list = new element[15000];
	this->n = smatA.n;
	int iterA = 1;
	int iterB = 1;
	this->cnt = 0;

	for (int i = 1; i <= smatA.cnt + smatBT.cnt; i++)
	{
		if (smatA.list[iterA].row == smatBT.list[iterB].row)
		{
			if(smatA.list[iterA].col == smatBT.list[iterB].col)
				list += 
		}
	}
	this->list[0].val = this->cnt;
	this->list[0].col = smatA.n;
	this->list[0].row = smatA.n;

	//printf("=============================================================\n");
	//for (int i = 0; i <= this->list[0].val; i++)
	//{
	//	printf("Ccnt : %d, row: %d, col: %d, val: %d\n", i, this->list[i].row, this->list[i].col, this->list[i].val);
	//}
}