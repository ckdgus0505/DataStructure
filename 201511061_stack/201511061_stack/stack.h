#include <stdio.h>
#include <stdlib.h>
#include <stack>

class pos {
public:
	int y;
	int x;
	pos(int _y, int _x);
	pos();
};

class stack {
private:
	int top;
	int n;
	pos *arr;
public:
	void init(int _n);
	bool is_empty();
	bool is_full();
	void push(pos _pos);
	pos pop();
	pos tak();
};