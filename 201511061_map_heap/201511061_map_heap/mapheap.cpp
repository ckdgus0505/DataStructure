#define _CRT_SECURE_NO_WARNINGS
#include "mapheap.h"
char* ret_key;

std::vector<hnode> Vheap;


void node::init()
{
	this->key = (char*)malloc(sizeof(char)*64);
	strcpy(this -> key, "");
	this->value = 0;
	this->lchild = this->rchild = NULL;
	this->parent = NULL;
}

void node::insert(char* ikey)
{
	int i = 0;
	char tmp[64];

	for (int i = 63; i >=0; i--)
	{
		if (ikey[i] == '\0') // 앞의 괄호 열기도 없애줘야함
			if (!(ikey[i-1] >= 'a' && ikey[i-1] <= 'z' || ikey[i] >= 'A' && ikey[i] <= 'Z') )
				ikey[i - 1] = '\0';
	}

	if (strcmp(this->key, "") == 0)
	{
		strcpy(this->key, ikey);
		this->value = 1;
	}

	if (strcmp(ikey, this->key) == 0)
	{
		this->value++;
	}
	else if (strcmp(ikey, this->key) > 0) {
		if (this->rchild != NULL)
		{
			this->rchild->parent = this;
			this->rchild->insert(ikey);
		}
		else {
			this->rchild = (node*)malloc(sizeof(node));
			this->rchild->set(ikey);
			this->rchild->parent = this;
		}
	}
	else {
		if (this->lchild != NULL)
		{
			this->lchild->parent = this;
			this->lchild->insert(ikey);
		}
		else {
			this->lchild = (node*)malloc(sizeof(node));
			this->lchild->set(ikey);
			this->lchild->parent = this;
		}
	}
}
int node::remove(char* dkey)
{
	// dkey와 key와 같으면
	if (strcmp(dkey, this->key) == 0) {
		printf("Deleting % s\n", dkey);
			// (1) 두 child가 다 NULL
		if (this->lchild == NULL && this->rchild == NULL)
		{
			int ret = this ->value;
			strcpy(ret_key, this->key);
			if (this->parent != NULL)
			{
				if (this->parent->lchild == this) this->parent->lchild = NULL;
				else this->parent->rchild = NULL;
			}
			else return 0;
			free(this);
			return ret;
		}
			// (2-1) lchild만 NULL
		else if (this->lchild == NULL && this->rchild != NULL)
		{
			int ret = this->value;
			strcpy(ret_key, this->key);
			nptr leftmost = this->rchild;
			while (leftmost->lchild != NULL)
				leftmost = leftmost->lchild;
			strcpy(this->key, leftmost->key);
			this->value = leftmost->value;

			leftmost->parent->lchild = NULL;
			free(leftmost);

			return ret;
		}
			// (2-2) rchild만 NULL
		else if (this->lchild != NULL && this->rchild == NULL)
		{
			int ret = this->value;
			strcpy(ret_key, this->key);
			nptr rightmost = this->lchild;
			while (rightmost->rchild != NULL)
				rightmost = rightmost->lchild;
			strcpy(this->key, rightmost->key);
			this->value = rightmost->value;
			
			rightmost->parent->rchild = NULL;
			free(rightmost);

			return ret;
		}
			// (3) 둘 다 NULL이 아닌 경우
		else
		{
			int ret = this->value;
			strcpy(ret_key, this->key);
			nptr leftmost = this->rchild;
			while (leftmost->lchild != NULL)
				leftmost = leftmost->lchild;
			strcpy(this->key, leftmost->key);
			this->value = leftmost->value;

			leftmost->parent->lchild = NULL;
			free(leftmost);

			return ret;
		}
	}
	// dkey가 key보다 작으면
	else if (dkey < this->key) {
		this->lchild->remove(dkey);
	}
	// dkey가 key보다 크면
	else {
		this->rchild->remove(dkey);
	}
}

nptr node::find_smallest_child()
{
	if (this->lchild == NULL) return this;
	while (true)
	{
		if (this->lchild == NULL) break;
		else
		{
			return this->lchild->find_smallest_child();
		}
	}
	if (this->lchild == NULL) return NULL;
	else return this;
}

void node::set(char* skey)
{
	this->key = (char*)malloc(sizeof(char) * 64);
	strcpy(this->key, skey);
	this->value = 1;
	this->lchild = this->rchild = 0;
}
int node::Find(char* skey)
{
	if (strcmp(this->key, skey) == 0)
		return this->value;
	int temp;
	if (strcmp(this->key, skey) < 0 && this->rchild != NULL) {
		temp = this->rchild->Find(skey);
		if (temp > 0)
			return temp;
	}
	if (strcmp(this->key, skey) > 0 && this->rchild != NULL) {
		temp = this->lchild->Find(skey);
		if (temp > 0)
			return temp;
	}
	return 0;
}

char* node::get_data()
{
	return this->key;
}

int node::get_cnt()
{
	return this->value;
}

bool is_word(char* input)
{
	if (input[0] >= 'a' && input[0] <= 'z' || input[0] >= 'A' && input[0] <= 'Z')
		return true;
	else return false;
}

void hnode::set(int num, char* skey)
{
	this->key = (char*)malloc(sizeof(char) * 64);
	strcpy(this->key, skey);
	this->value = num;
}

char* hnode::get_data()
{
	return this->key;
}
int hnode::get_cnt()
{
	return this->value;
}
bool greater(hnode a, hnode b)
{
	return a.get_cnt() < b.get_cnt() ? false : true;

}
void heap::init()
{
	std::make_heap(Vheap.begin(), Vheap.end(), greater);
	//this->arr = (hnode*)malloc(sizeof(hnode) * 10000); // 10000은 임의의 수
	//size = 0;
}
void heap::push(hnode _data)
{
	Vheap.push_back(_data);
	std::push_heap(Vheap.begin(), Vheap.end(), greater);

	//int i;
	//i = ++(this->size);

	//while (i != 1 && _data.get_cnt() > this->arr[i / 2].get_cnt()) // 부모노드와 비교 
	//{
	//	this->arr[i] = this->arr[i / 2];
	//	i /= 2;
	//}
	//this->size++;
	//this->arr[i] = _data;
}
hnode heap::pop()
{
	hnode ret = Vheap.front();
	
	std::pop_heap(Vheap.begin(), Vheap.end(), greater);
	Vheap.pop_back();
	return ret;

	//int parent = 1, child = 2;
	//int data, temp;

	//data = this->arr[parent].get_cnt();
	//temp = this->arr[(this->size)--].get_cnt(); // 삭제에 의한 size 감소 

	//while (child <= this->size)
	//{
	//	// 자식 노드간 큰 수 비교  
	//	if (child < this->size && this->arr[child] < this->arr[child + 1])
	//		child++;

	//	if (temp >= this->arr[child].get_cnt()) break;

	//	this->arr[parent] = this->arr[child].get_cnt();
	//	parent = child;
	//	child *= 2; // 다음 자식 노드와 비교 
	//}

	//h->heap[parent] = temp;
	//return data;
}

void node::indorder()
{
	printf("%s ", this->key);

	if (this->lchild != NULL)
	this->lchild->indorder();

	if (this->rchild != NULL)
	this->rchild->indorder();
}