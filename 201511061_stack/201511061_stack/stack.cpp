#include "stack.h"
pos::pos(int _y, int _x)
{
	y = _y;
	x = _x;
}
pos::pos()
{}

void stack::init(int _n)
{
	top = 0;
	n = _n;
	arr = (pos*)malloc(sizeof(pos) * n);
}
bool stack::is_empty()
{
	if (top == 0) return true;
	else return false;
}
bool stack::is_full()
{
	if (top > n) return true;
	else return false;
}
void stack::push(pos _pos)
{
	if (!is_full())
	{
		arr[top++] = _pos;
	}
	else
	{
		n = 2 * n;
		arr = (pos*)realloc(arr, sizeof(pos) * n);

		arr[top++] = _pos;
	}
}
pos stack::pop()
{
	if (!is_empty()) return arr[--top];
	else
	{
		printf("The stack is Empty\n");
		printf("you can't pop any more!\n");
		exit(1);
	}
}
pos stack::tak()
{
	if (!is_empty()) return arr[top];
	else
	{
		printf("The stack is Empty\n");
		exit(1);
	}
}