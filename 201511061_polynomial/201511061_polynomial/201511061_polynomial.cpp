#define _CRT_SECURE_NO_WARNINGS
#include "poly.h"

int main()
{
	polynomial pA, pB, pC, pD;
	FILE* fp = fopen("poly.txt", "r+t");
	pA.load(fp);
	pB.load(fp);

	printf("poly A is....................................\n");
	pA.print();
	printf("\npoly B is....................................\n");
	pB.print();
	pC.zero();
	printf("\npoly C is....................................\n");
	pC.print();
	pC.add(pA, pB);
	printf("\nAddition....................................\n");
	pC.print();
	pD.zero();
	printf("\npoly D is....................................\n");
	pD.print();
	pD.multiply(pA, pB);
	printf("\nMultiplication....................................\n");
	pD.print();
	fclose(fp);
	system("pause");
	return 0;
}