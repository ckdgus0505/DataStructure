#define _CRT_SECURE_NO_WARNINGS
#include "tree.h"

void node::init()
{
	this->name = (char*)malloc(sizeof(char) * 16);
	strcpy(this->name, "-1");
	this->nchilds = 0;
}
bool  node::is_empty()
{
	if (strcmp(this->name, "-1") == 0)
		return true;
	return false;
}

void  node::set(char nname[16])
{
	strcpy(this->name, nname);
	this->nchilds = 0;
}

// cnames[0]: 부모
// cnames[1] ~ cnames[n_child-1]: 자식들
// n_child: 자식의 수 + 1
void node::insert(int n_child, char cnames[][16])
{
// (1) root node에 삽입
	if (strcmp(this->name, "-1") == 0)
	{
		strcpy(this->name, cnames[0]);
		this->nchilds = n_child - 1; // -1은 본인
		this->childs = (nptr*)malloc(sizeof(nptr) * (n_child));
		this->childs[0] = (nptr)malloc(sizeof(node));
		this->childs[0]->name = (char*)malloc(sizeof(char) * 16);
		strcpy(this->childs[0]->name, "root");
		for (int i = 1; i < n_child; i++)
		{
			this->childs[i] = (nptr)malloc(sizeof(node));
			this->childs[i]->name = (char*)malloc(sizeof(char) * 16);
			strcpy(this->childs[i]->name, cnames[i]);
		}
		return;
	}
// (2) current node에 삽입
	if (strcmp(this->name, cnames[0]) == 0)
	{
		this->nchilds = n_child - 1; // -1은 본인
		this->childs = (nptr*)malloc(sizeof(nptr) * (n_child));
		this->childs[0] = (nptr)malloc(sizeof(node));
		this->childs[0]->name = (char*)malloc(sizeof(char) * 16);
		//strcpy(this->childs[0]->name, "root"); => 이게 사실 조상이되어야 함
		for (int i = 1; i < n_child; i++)
		{
			this->childs[i] = (nptr)malloc(sizeof(node));
			this->childs[i]->name = (char*)malloc(sizeof(char) * 16);
			strcpy(this->childs[i]->name, cnames[i]);
		}
		return;
	}
// (3) child node에 삽입
	else
	{
		int i;
		for (i = 1; i <= this->nchilds; i++)
		{
			this->childs[i]->insert(n_child, cnames);
		}
	}
}

int  node::get_childs(char cnames[][16], char pname[16])
{
// (1) name과 pname이 같으면
	if (strcmp(this->name, pname) == 0)
	{
		for(int i = 1; i < nchilds; i++)
			strcpy(cnames[i-1], childs[i]->name);
		return this->nchilds;
	}
// (2) 모든 자식들에 대해서 get_childs ( )를 수행
	else
	{
		for (int i = 1; i < nchilds; i++)
		{
			this->childs[i]->get_childs(cnames, pname);
		}
	}
}

char* node::get_parent(char cname[16])
{
// (1) childs 중에 name이 cname인 child가 있으면
	if (strcmp(this->name, cname) == 0)
	{
		return this->childs[0]->name;
	}
// (2) 모든 자식들에 대해서 get_parent ( )를 수행
	else
	{
		for (int i = 1; i < nchilds; i++)
		{
			this->childs[i]->get_parent(cname);
		}
	}
}

int  node::has_child(char cname[16])
{
// childs 중 하나의 name이 cname과 같으면
	for (int i = 1; i < this->nchilds; i++)
	{
		if(strcmp(childs[i]->name, cname) == 0)
			return 1;
	}
	return 0;
}

int  node::get_siblings(char siblings[][16], char cname[16])
{
// (1) childs 중에 name이 cname과 같은 node가 있으면
	if (has_child(cname))
	{
	// siblings에 다른 childs의 name을 저장하고
		int cnt = 0;
		for (int i = 1; i < nchilds; i++)
		{
			if (strcmp(cname, childs[i]->name) == 0)
			{
				strcpy(siblings[cnt++], childs[i]->name);
			}
		}
	// nchilds – 1을 리턴
		return nchilds - 1;
	}
// (2) childs에 대해서 get_siblings ( )을 수행
}

void  node::traverse()
{
// current node의 name과 childs의 name들을 출력
	printf("[%s] :", name);
	for (int i = 1; i <= this->nchilds; i++)
	{
		printf(" %s", childs[i]->name);
	}
	printf("\n");
// 모든 childs에 대해서 traverser ( ) 수행
	for (int i = 1; i <= this->nchilds; i++)
	{
		this->childs[i]->traverse();
	}
}

int parse_str(char toks[][16], char* str)
{
	int spacecnt = 0;
	int cnt = 0;
	int i = 0;
	int j = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] == ' ' || str[i] == '\n'))
		{
			spacecnt = 0;
			toks[cnt][j] = str[i];
			i++;
			j ++;
		}
		else if ((str[i] == ' ' || str[i] == '\n') && spacecnt == 0)
		{
			spacecnt++;
			toks[cnt][j] = '\0';
			cnt++;
			i++;
			j = 0;
		}
	}
	return cnt;
}