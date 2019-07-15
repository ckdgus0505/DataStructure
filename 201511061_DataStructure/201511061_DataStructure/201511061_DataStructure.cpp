#define _CRT_SECURE_NO_WARNINGS
#include "sparse.h"
#include <time.h>

int n;
int** matA;
int** matB;
int** matC;

smatrix smatA;
smatrix smatB;
smatrix smatC;
smatrix smatBT;

extern void load(FILE* fpA, FILE* fpB);
extern int** transpose(int n, int** mat);
extern int** add(int n, int** matA, int** matB);
extern int** mult(int n, int** matA, int** matB);

int main()
{

	clock_t tik, tok;
	// 1. load
	FILE* fpA = fopen("matA\\matA_K.txt", "r+t");
	FILE* fpB = fopen("matB\\matB_K.txt", "r+t");
	tik = clock();
	load(fpA, fpB);
	tok = clock();
	printf("loading time: %f\n", (float)(tok - tik) / CLOCKS_PER_SEC);
	fclose(fpA);
	fclose(fpB);

	// matA와 matB에 행렬이 저장

	// matA->smatA, matB->smatB
	tik = clock();
	smatA.convert_to_smatrix(n, matA);
	tok = clock();
	printf("smatA.convert_to_smatrix: %f\n", (float)(tok - tik) / CLOCKS_PER_SEC);
	tik = clock();
	smatB.convert_to_smatrix(n, matB);
	tok = clock();
	printf("smatB.comver_to_smatrix: %f\n", (float)(tok - tik) / CLOCKS_PER_SEC);

// 2. transpose
	// 2.1 ordinary transpose
	tik = clock();
	matC = transpose(n, matA);
	tok = clock();
	printf("transpose: %f\n", (float)(tok - tik) / CLOCKS_PER_SEC);
	// 2.2 fastTranspose
	tik = clock();
	smatBT.fastTranspose(smatB);
	tok = clock();
	printf("fastTranspose: %f\n", (float)(tok - tik) / CLOCKS_PER_SEC);
// 3. add
	// 3.1 ordinary add
	tik = clock();
	matC = add(n, matA, matB);
	tok = clock();
	printf("add: %f\n", (float)(tok - tik) / CLOCKS_PER_SEC);

	// 3.2 fastAdd
	tik = clock();
	smatC.fastAdd(smatA, smatB);
	tok = clock();
	printf("fastadd: %f\n", (float)(tok - tik) / CLOCKS_PER_SEC);
// 4. multiply
	// 4.1 ordinary multiply
	tik = clock();
	matC = mult(n, matA, matB);
	tok = clock();
	printf("multiply: %f\n", (float)(tok - tik) / CLOCKS_PER_SEC);

	// 4.2 fastMult
	tik = clock();
	smatC.fastMult(smatA, smatBT);
	tok = clock();
	printf("fastMultiply: %f\n", (float)(tok - tik) / CLOCKS_PER_SEC);

	system("pause");
	return 0;
}