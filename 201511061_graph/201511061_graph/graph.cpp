#define _CRT_SECURE_NO_WARNINGS

#include "graph.h"
extern int dfn[];
extern int low[];
extern int num;

typedef std::pair<int, int> ver; // u,w 담는 pair
std::vector<ver> stack; // 방문하는 vertex 담는 stack

void graph::load_graph(FILE* fp)
{
	int data1; int data2;
	fscanf(fp, "%d", &data1);
	fscanf(fp, "%d", &data2);

	this->n = data1;
	this->m = data2;
	this->alist = (anode*)malloc(sizeof(anode) * n+1);
	for (int i = 0; i <= n; i++)
	{
		alist[i].head = (nptr)malloc(sizeof(node));
		alist[i].vtx = i;
		alist[i].head->vtx = -1;
		alist[i].head->next = NULL;
		this->alist[i].tail = alist[i].head;
	}

	for (int i = 0; i < m; i++)
	{
		nptr tmp1 = (nptr)malloc(sizeof(node));
		nptr tmp2 = (nptr)malloc(sizeof(node));
		if (fscanf(fp, "%d", &data1) != NULL) tmp2->vtx = data1;
		if (fscanf(fp, "%d", &data2) != NULL) tmp1->vtx = data2;
		tmp1->vtx = data2;
		tmp2->vtx = data1;

		if (this->alist[data1].head == this->alist[data1].tail)
		{
			tmp1->next = alist[data1].tail;
			this->alist[data1].head = tmp1;
		}
		else if (this->alist[data1].head->vtx > tmp1->vtx)
		{
			tmp1->next = alist[data1].head;
			alist[data1].head = tmp1;
		}
		else
		{
			nptr tmptr = this->alist[data1].head;
			for(; tmptr->next != NULL;)
			{
				if (tmptr->next->vtx == -1) break;
				if (tmptr->next->vtx < tmp1->vtx)
					tmptr = tmptr->next;
				else break;
			}
			tmp1->next = tmptr->next;
			tmptr->next = tmp1;
		}

		if (this->alist[data2].head == this->alist[data2].tail)
		{
			tmp2->next = alist[data2].tail;
			this->alist[data2].head = tmp2;
		}
		else if (this->alist[data2].head->vtx > tmp2->vtx)
		{
			tmp2->next = alist[data2].head;
			alist[data2].head = tmp2;
		}
		else
		{
			nptr tmptr = this->alist[data2].head;
			for (; tmptr->next != NULL;)
			{
				if (tmptr->next->vtx == -1) break;
				if (tmptr->next->vtx < tmp2->vtx)
					tmptr = tmptr->next;
				else break;
			}
			tmp2->next = tmptr->next;
			tmptr->next = tmp2;
		}
	}

}
void graph::print_graph()
{
	for (int i = 1; i <= this->n; i++)
	{
		printf("%d: ", i);
		nptr tmptr = this->alist[i].head;
		while (tmptr != alist[i].tail)
		{
			printf("%d ", tmptr->vtx);
			tmptr = tmptr->next;
		}
		printf("\n");
	}

}
void graph::dfs(int u, int v)
{
	ver tmp;
	dfn[u] = low[u] =  num++;
	node* vertex = alist[u].head;
	for (int w = vertex->vtx; true; vertex = vertex->next, w = vertex->vtx)
	{
		if (vertex->vtx == -1) break;
		if (dfn[w] < 0)
		{
			stack.push_back(ver(u, w)); //
			dfs(w, u);
			low[u] = min(low[u], low[w]);
			if (low[w] >= dfn[u])
			{
				printf("new bicon: %d\n", u);
				do {
					tmp = stack.back(); //
					stack.pop_back();
					printf("<%d, %d> ", tmp.first, tmp.second);//
				} while (tmp.first != u || tmp.second != w);
				printf("\n");
			}
		}
		else if (w != v)
			low[u] = min(low[u], low[w]);
	}
}