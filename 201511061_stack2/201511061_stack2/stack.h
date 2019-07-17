#include <stdio.h>
#include <stdlib.h>

class stack1 {
private:
	int top;
	int n;
	char* arr;
public:
	void init(int _n);
	bool is_empty();
	bool is_full();
	void push(char _char);
	void remove_delimiters(char* _expr2, char* _expr);
	pos pop();
	pos peek();
};