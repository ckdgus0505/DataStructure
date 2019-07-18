#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class stack2 {
private:
	int top;
	int n;
	double* arr;

public:
	void init();
	bool is_empty();
	bool is_full();
	void push(double _num);
	double pop();
	double peek();
};