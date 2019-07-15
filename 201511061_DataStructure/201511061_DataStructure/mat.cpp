#define _CRT_SECURE_NO_WARNINGS
#include "sparse.h"


extern int n;
extern int** matA;
extern int** matB;
extern int** matC;

// 1. load
void load(FILE* fpA,  FILE* fpB)
{
	//fp = fopen("", "");
	// fp에 지정된 file에서 n x n 크기의 행렬을 저장
	int data;
	int i = 0;
	if(fscanf(fpA, "%d", &n) != NULL)
	{
		matA = new int* [n];
		for (int i = 0; i < n; i++)
			matA[i] = new int[n];
		

		while (fscanf(fpA, "%d", &data) != EOF)
		{
			matA[i / n][i % n] = data;
			i++;
		}

	}
	i = 0;
	if (fscanf(fpB, "%d", &n) != NULL)
	{
		matB = new int* [n];
		for (int i = 0; i < n; i++)
			matB[i] = new int[n];
		

		while (fscanf(fpB, "%d", &data) != EOF)
		{
			matB[i / n][i % n] = data;
			i++;
		}
	}

}
// 2. transpose
int** transpose(int n, int** mat)
{
	matC = new int* [n];
	for (int i = 0; i < n; i++)
		matC[i] = new int[n];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matC[i][j] = mat[j][i];
		}
	}
	return matC;
}
// 3. add
int** add(int n, int** matA, int** matB)
{
	matC = new int* [n];
	for (int i = 0; i < n; i++)
		matC[i] = new int[n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matC[i][j] = matA[i][j] + matB[i][j];
		}
	}
	return matC;
}
// 4. multiply
int** mult(int n, int** matA, int** matB)
{
	matC = new int* [n];
	for (int i = 0; i < n; i++)
		matC[i] = new int[n];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matC[i][j] = 0;
			for (int k = 0; k < n; k++)
				matC[i][j] *= matA[i][j] * matB[i][j];
		}
	}
	return matC;
}