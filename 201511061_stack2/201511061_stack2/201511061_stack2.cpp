#include "stack1.h"
#include "stack2.h"

stack1 tok;

int main()
{
	char expr[256] = "31.6 + (19.3 - 2.1)*((1.4^0.6) + 8.5)";
	char expr2[256];
	tok.init();
	remove_delimiters(expr2, expr);
	token_parser(expr2);
	tok.print_tok();
	//postpix();
	//print_tok(ptcnt, ptok);
	//evaluate();
	system("pause");
	return 0;
}