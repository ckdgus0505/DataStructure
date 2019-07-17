#include "stack1.h"

void stack1::init(int _n)
{
	top = 0;
	n = _n;
	arr = (pos*)malloc(sizeof(pos) * n);
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
void stack1::push(pos _pos)
{
	if (!is_full())
	{
		arr[top++] = _pos;
	}
	else
	{
		n = 2 * n;
		if (!(arr = (pos*)realloc(arr, sizeof(pos) * n)) == NULL);
		else
		{
			printf("realloc error\n");
			exit(1);
		}

		arr[top++] = _pos;
	}
}
void stack1::remove_delimiters(char* _expr2, char* _expr)
{
	
}
pos stack1::pop()
{
	if (!is_empty()) return arr[--top];
	else
	{
		printf("The stack is Empty\n");
		printf("you can't pop any more!\n");
		exit(1);
	}
}
pos stack1::peek()
{
	if (!is_empty()) return arr[top];
	else
	{
		printf("The stack is Empty\n");
		exit(1);
	}
}