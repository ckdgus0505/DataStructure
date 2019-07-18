#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class stack1 {
private:
	int top;
	int opcnt;
	int odcnt;
	int n;
	int* tok;
	char** od;
	char** op;
public:
	void init();
	bool is_empty();
	bool is_full();
	void push(char* _tok);
	char* pop();
	char* peek();
	void print_tok();
	void postpix();
	void evaluate();
};

void append(char* dst, char c);
void remove_delimiters(char* _expr2, char* _expr);
void token_parser(char* _expr);