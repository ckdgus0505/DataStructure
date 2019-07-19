#define _CRT_SECURE_NO_WARNINGS
#include "stack1.h"
#include "stack2.h"
#include <math.h>

extern stack1 tok;
extern stack1 ptok;
extern stack2 result;

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
		if (_tok[0] >= '0' && _tok[0] <= '9') // 숫자
		{
			tok[top++] = odcnt;
			strcpy(od[odcnt++], _tok);
		}
		else
		{
			tok[top++] = -1 * opcnt;  // 음수면 op
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
			return od[--odcnt];
		}
		else if (tok[top - 1] < 0)
		{
			top--;
			return op[--opcnt];
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
	char tmp[7];
	if (!is_empty())
	{
		if (tok[top - 1] > 0)
		{
			return od[odcnt-1];
		}
		else
		{
			return op[opcnt-1];
		}
	}
	else
	{
		printf("The stack is Empty\n");
		//exit(1);
	}
}

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
	tok.init();
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

void stack1::postpix()
{
	char* tmp = (char*)malloc(sizeof(char) * 7);
	stack1 opstack;
	opstack.init();
	ptok.init();
	int N = top;
	for (int i = 0; i < N; i++)
	{

		if (tok[i] > 0) // operand
		{
			ptok.push(od[tok[i]]);
		}
		else // opcode
		{
			strcpy(tmp, op[-1*tok[i]]);
			if (strcmp(tmp, "(") == 0)
				opstack.push(tmp);
			else if (strcmp(tmp, ")") == 0)
			{
				while (strcmp(opstack.peek(), "(") != 0)
				{
					strcpy(tmp, opstack.pop());
					ptok.push(tmp);
				}
				opstack.pop();
			}
			else if ((opstack.top == 0))
			{
				opstack.push(tmp);
			}
			else if ((strcmp(opstack.peek(),"*")==0 || strcmp(opstack.peek(), "/") == 0 || strcmp(opstack.peek(), "%") == 0) && (strcmp(tmp, "+") == 0 || strcmp(tmp, "-") == 0)) // ^ 추가 안되어있음ㅠ 우선순위 지정하는 함수 만드는게 좋음
			{
				ptok.push(opstack.pop());
				opstack.push(tmp);
			}
			else opstack.push(tmp);

		}
	}
	while (!opstack.is_empty())
		ptok.push(opstack.pop());
}

void stack1::evaluate()
{
	result.init();
	int N = top;
	for ( int i = 0; i < N; i++)
	{
		if (tok[i] > 0)
			result.push(atof(od[tok[i]]));
		else
		{
			char currtok = op[-1 * tok[i]][0];
			double od1 = result.pop();
			double od2 = result.pop();
			switch (currtok) 
			{ 
				case '+':
					result.push(od2 + od1);
					break;
				case '-':
					result.push(od2 - od1);
					break;
				case '*':
					result.push(od2 * od1);
					break;
				case '/':
					result.push(od2 / od1);
					break;
				case '%':
					result.push((int)od2 % (int)od1);
					break;
				case '^':
					result.push(pow(od2, od1));
					break;
			}
		}

	}
	printf("%f\n",result.pop());
}