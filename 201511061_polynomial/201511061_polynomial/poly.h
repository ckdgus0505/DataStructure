#include <stdio.h>
#include <stdlib.h>
class term {
public:
	int coef;
	int exp;

	term *next;
};

class polynomial {
	int degree;
	term* head;
public:
	void zero();
	bool is_zero();
	int coef(int exp);
	int LeadExp();
	void append(int _coef, int _exp);
	void insert(int _coef, int _exp);
	void load(FILE* fp);
	void add(polynomial pA, polynomial pB);
	void multiply(polynomial pA, polynomial pB);
	void print();
};