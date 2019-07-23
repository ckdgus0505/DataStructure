#define _CRT_SECURE_NO_WARNINGS
#define MAX_VERTEX 100
#include "graph.h"
graph g1;
int dfn[MAX_VERTEX];
int low[MAX_VERTEX];
int num = 1;

int main()
{
	FILE* fp = fopen("graph02.txt", "r+t");
	g1.load_graph(fp);
	fclose(fp);
	g1.print_graph();

	memset(dfn, -1, sizeof(dfn));
	memset(low, -1, sizeof(low));

	g1.dfs(1, -1);
	system("pause");
	return 0;
}