#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#define min(a,b) a<b?a:b
typedef class node* nptr;
class node {
public:
	int vtx;
	nptr next;
};

class anode {
public:
	int vtx;
	int dfn, low;
	nptr head, tail;
};

class graph {
	int n, m;  // n : vertex 개수, m: edge 개수
	anode* alist;
public:
	void load_graph(FILE* fp);
	void print_graph();
	void dfs(int u, int v);
};