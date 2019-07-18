#include "stack1.h"
#include "stack2.h"

stack1 tok;
stack1 ptok;
stack2 result;

int main()
{
	char expr[256] = "((3+4)*8-7)/2"; //"31.6 + (19.3 - 2.1)*((1.4^0.6) + 8.5)";
	char expr2[256];

	remove_delimiters(expr2, expr);
	token_parser(expr2);
	tok.print_tok(); // ¼º°ø
	tok.postpix();
	ptok.print_tok();
	ptok.evaluate();
	system("pause");
	return 0;
}