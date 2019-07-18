#define _CRT_SECURE_NO_WARNINGS
#include "stack2.h"

void stack2::init()
{
	top = 0;
	n = 100;
	arr = (double*)malloc(sizeof(double) * n);
}
bool stack2::is_empty()
{
	if (top == 0) return true;
	else return false;
}
bool stack2::is_full()
{
	if (top >= n) return true;
	else return false;
}
void stack2::push(double _num)
{
	if (!is_full())
	{
		arr[top++] = _num;
	}
	else
	{
		n = 2 * n;
		if (!(arr = (double*)realloc(arr, sizeof(arr) * n)) == NULL);
		else
		{
			printf("realloc error\n");
			exit(1);
		}

		arr[top++] = _num;
	}
}
double stack2::pop()
{
	if (!is_empty()) return arr[--top];
	else
	{
		printf("The stack is Empty\n");
		printf("you can't pop any more!\n");
		exit(1);
	}
}
double stack2::peek()
{
	char tmp[7];
	if (!is_empty()) return arr[top - 1];
	else
	{
		printf("The stack is Empty\n");
		//exit(1);
	}
}