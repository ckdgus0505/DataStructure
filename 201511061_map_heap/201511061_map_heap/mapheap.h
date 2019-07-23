#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include<vector>
#include<algorithm>
typedef class node* nptr;
class node {
private:
	char* key;
	int value;
	nptr lchild, rchild, parent;

public:
	// �ʿ��� ���� ����
	void init();
	void set(char* skey);
	int Find(char* skey);
	void insert(char*ikey);
	int remove(char* dkey);
	nptr find_smallest_child();
	
	char* get_data();
	int get_cnt();

	void indorder();
};

class hnode {
private:
	char* key;
	int value;

public:
	void set(int num, char* skey);
	char* get_data();
	int get_cnt();
};
class heap {
private:
	hnode data;
	hnode* arr;
	int size;

public:
	void init();
	// ������ ����
	void push(hnode _data);
	hnode pop();
};

bool is_word(char* input);

