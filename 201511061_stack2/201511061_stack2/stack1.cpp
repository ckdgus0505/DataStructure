#define _CRT_SECURE_NO_WARNINGS
#include "stack1.h"

extern stack1 tok;

void stack1::init()
{
	top = 0;
	n = 100;
	opcnt = 1;
	odcnt = 1;
	tok = (int*)malloc(sizeof(int) * n);
	op = (char**)malloc(sizeof(char*) * n);
	for (int i = 0; i < n; i++)
	{
		op[i] = (char*)malloc(sizeof(char));
	}
	od = (char**)malloc(sizeof(char*) * n);
	for (int i = 0; i < n; i++)
	{
		od[i] = (char*)malloc(sizeof(char)*7);
	}
}
bool stack1::is_empty()
{
	if (top == 0) return true;
	else return false;
}
bool stack1::is_full()
{
	if (top >= n) return true;
	else return false;
}
void stack1::push (char* _tok)
{

	if (!is_full())
	{
		if (_tok[0] >= '0' && _tok[0] <= '9') // ¼ýÀÚ
		{
			tok[top++] = odcnt;
			strcpy(od[odcnt++], _tok);
		}
		else
		{
			tok[top++] = -1 * opcnt;
			strcpy(op[opcnt++], _tok);
		}
	}
	else
	{
		printf("stack full!!\n");
		return;
	}

}
char* stack1::pop()
{
	if (!is_empty())
	{
		char tmp[7];
		if (tok[top - 1] > 0) // od
		{
			top--;
			return od[odcnt--];
		}
		else if (tok[top - 1] < 0)
		{
			top--;
			return op[opcnt--];
		}
	}
	else
	{
		printf("The stack is Empty\n");
		printf("you can't pop any more!\n");
		exit(1);
	}
}
char* stack1::peek()
{
	if (!is_empty())
	{
		if (tok[top - 1] >= 0)
			return od[opcnt];
		else return op[opcnt];
	}
	else
	{
		printf("The stack is Empty\n");
		exit(1);
	}
}
int stack1::get_opcnt() { return opcnt; }
int stack1::get_odcnt() { return odcnt; }

void stack1::print_tok()
{
	for (int i = 1; i < opcnt; i++)
	{
		printf("op token %d: %s\n", i, op[i]);
	}
	printf("\n");
	for (int i = 1; i < odcnt; i++)
	{
		printf("od token %d: %s\n", i, od[i]);
	}
	printf("\n");
	int p = 1;
	int d = 1;
	for (int i = 0; i < top; i++)
	{
		if (tok[i] > 0)
			printf("%s", od[d++]);
		else
			printf("%s", op[p++]);
	}
	printf("\n");
}


void remove_delimiters(char* _expr2, char* _expr)
{
	strcpy(_expr2,"\0");
	for (int i = 0; i < 256; i++)
	{
		if (!(_expr[i] == ' ') && !(_expr[i] == '\t') && !(_expr[i] == '\n'))
		{
			append(_expr2, _expr[i]);
		}
		if (_expr[i] == '\0') break;
	}
}
void token_parser(char* _expr)
{
	char* tmp;
	char* op;
	tmp = (char*)malloc(sizeof(int) * 10);
	op = (char*)malloc(sizeof(int) * 2);
	strcpy(tmp, "\0");
	for(int i = 0; i < 256; i++)
	{
		if (_expr[i] == '\0')
		{
			if (strcmp(tmp, "\0"))
				tok.push(tmp);
			break;
		}
		if ( (_expr[i] >= '0' && _expr[i] <= '9') || _expr[i] == '.' )
		{
				append(tmp, _expr[i]);
		}
		else
		{
			if (strcmp(tmp, "\0")) // tmp != "\0"
			{
				tok.push(tmp);
				strcpy(tmp, "\0");
			}
			strcpy(op, "\0");
			append(op, _expr[i]);
			tok.push(op);
		}
	}
}
void append(char* dst, char c) {
	char* p = dst;
	while (*p != '\0') p++;
	*p = c;
	*(p + 1) = '\0';
}
