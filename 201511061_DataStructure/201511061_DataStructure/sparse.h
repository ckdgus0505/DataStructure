#include <stdio.h>
#include <stdlib.h>
class element {
public:
	int row;
	int col;
	int val;
};

class smatrix {
	int n;
	int cnt;
	element* list;

	int* startPos, * rowTerms;

public:
	void convert_to_smatrix(int x, int** mat); // ¼±¾ð
	void ready();
	void fastTranspose(smatrix smat);
	void fastAdd(smatrix  smatA, smatrix smatB);
	void fastMult(smatrix  smatA, smatrix smatB);
};