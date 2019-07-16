#define _CRT_SECURE_NO_WARNINGS
#include "stack.h"

void load_maze(FILE* fp);
void print_maze();
void solve_maze();
int x, y; // 미로 사이즈
char** maze;
stack route; // 경로를 저장하는 stack
pos now;
pos Entry;
pos Exit;
int nbhd[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };
int main()
{
	FILE* fp = fopen("maze.txt", "r+t");

	load_maze(fp);

	print_maze();

	solve_maze();

	print_maze();

	fclose(fp);
	system("pause");
	return 0;
}
void load_maze(FILE* fp)
{
	char tmp;
	fscanf(fp, "%d", &x);
	fscanf(fp, "%d", &y);
	maze = (char**)malloc(sizeof(char*)*y);
	for (int i = 0; i < y; i++)
	{
		maze[i] = (char*)malloc(sizeof(char) * x);
	}
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			fscanf(fp, "%c", &tmp);
			if (tmp == ' ');
			else maze[i][j] = tmp;
			fscanf(fp, "%c", &tmp);
			if (tmp == ' ');
			else maze[i][j] = tmp;
			if (tmp == 'E') {
				Entry.y = i;
				Entry.x = j;
			}
			if (tmp == 'X') {
				Exit.y = i;
				Exit.x = j;
			}

		}
	}
}
void print_maze()
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			printf("%c ", maze[i][j]);
		}
		printf("\n");
	}
	printf("Entry: (%d, %d)\n", Entry.y, Entry.x);
	printf("Exit: (%d, %d)\n", Exit.y, Exit.x);
	printf("\n");
}

void solve_maze()
{
	int flage = 0;
	int flagx = 0;
	route.init(3 * x);

	now = Entry;
	maze[now.y][now.x] = '#';
	while (true)
	{
		int i;
		for(i = 0; i < 4; i++)
		{
			if (maze[now.y][now.x] == 'X') break;
			if (maze[now.y + nbhd[i][0]][now.x + nbhd[i][1]] == '0' || maze[now.y + nbhd[i][0]][now.x + nbhd[i][1]] == 'X')
			{

				route.push(now);
				now = pos(now.y + nbhd[i][0],now.x + nbhd[i][1]);
				maze[now.y][now.x] = '#';
				break;
			}
			if (i == 3 && maze[now.y + nbhd[i][0]][now.x + nbhd[i][1]] != '0')
			{
				maze[now.y][now.x] = 'x';
				now = route.pop();
			}
		}
		if (now.y == Exit.y && now.x == Exit.x)
		{
			route.push(now);
			now = pos(now.y + nbhd[i][0], now.x + nbhd[i][1]);
			maze[now.y][now.x] = '#';
			break;
		}
		if (route.is_empty())
		{
			printf("no exit!!\n");
			break;
		}
	}

}