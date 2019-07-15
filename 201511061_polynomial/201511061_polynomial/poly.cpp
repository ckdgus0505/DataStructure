#define _CRT_SECURE_NO_WARNINGS
#include "poly.h"

void polynomial::zero()
{
	head = (term*)malloc(sizeof(term));
	head->coef = 0;
	head->next = NULL;
}
bool polynomial::is_zero()
{
	return (head->coef == 0);
}
int polynomial::coef(int exp)
{
	term* curr;
	for (curr = head; curr != NULL; curr->next)
	{
		if (curr->exp == exp)
			return curr->coef;
	}
	return 0;
}
int polynomial::LeadExp()
{
	if (is_zero()) {
		printf("Zero polynormial\n");
		return 0;
	}
	return head->exp;
}
void polynomial::append(int _coef, int _exp)
{
// 예외 처리
	if (is_zero())
	{
		head->coef = _coef;
		head->exp = _exp;
		head->next = NULL;
		return;
	}
// 마지막 항으로 이동
	term* curr = head;
	int i = 0;
	while (curr->next != NULL) {
		curr = curr->next;
		i++;
	}
// 새로운 항을 만들어서 첨부
	if (curr->exp < _exp)
	{
		printf("Wrong function\n");
		printf("다항식을 내림차순으로 적어주세요\n");
		exit(0);
	}
	else
	{
		curr->next = new term;
		curr->next->coef = _coef;
		curr->next->exp = _exp;
		curr->next->next = NULL;
	}
}
void polynomial::insert(int _coef, int _exp)
{
// 예외처리
// 삽입할 위치를 결정
	term* curr = head;

	if (curr->exp > _exp)
	{
		while (true) {
			if (curr->next == NULL) break;
			if (curr->next->exp > _exp)
				curr = curr->next;
			else break;
		}
	}
	// 삽입할 위치가 마지막인 경우
	if (curr->next == NULL)
	{
		append(_coef, _exp);
	}
	// exp와 같은 지수를 가진 항이 있는 경우
	else if (curr->next->exp == _exp)
	{
		curr->next->coef += _coef;
		if (curr->next->coef == 0)
		{
			term* dnode = curr->next;
			curr->next = dnode->next;
			free(dnode);
		}
	}
	// exp와 같은 지수를 가진 항이 없는 경우
	else if (curr->next->exp < _exp)
	{
		term* dnode = new term;
		dnode->next = curr->next;
		curr->next = dnode;
		dnode->exp = _exp;
		dnode->coef = _coef;
	}


}
void polynomial::load(FILE* fp)
{
	int data;

	if (fscanf(fp, "%d", &data) != NULL)
	{
		zero();
		int _exp;
		int _coef;
		for (int i = 0; i < data * 2; i++)
		{
			if (i % 2 == 0)
				fscanf(fp, "%d", &_coef);
			else if (i % 2 == 1)
			{
				fscanf(fp, "%d", &_exp);
				append(_coef, _exp);
			}
		}
	}
}
void polynomial::add(polynomial pA, polynomial pB)
{
	term* iterA = pA.head;
	term* iterB = pB.head;
	this->zero();
	while (iterA != NULL && iterB != NULL)
	{
		if (iterA->exp > iterB->exp)
		{
			append(iterA->coef, iterA->exp);
			iterA = iterA->next;
		}
		else if (iterA->exp < iterB->exp)
		{
			append(iterB->coef, iterB->exp);
			iterB = iterB->next;
		}
		else
		{
			if (iterA->coef + iterB->coef != 0)
				append(iterA->coef + iterB->coef, iterA->exp);
			iterA = iterA->next;
			iterB = iterB->next;
			
		}
	}
}
void polynomial::multiply(polynomial pA, polynomial pB)
{
	term* iterA = pA.head;
	term* iterB;
	this->zero();

	while (true) // A
	{
		iterB = pB.head;
		while (true) // B
		{
			insert(iterA->coef * iterB->coef, iterA->exp + iterB->exp);
			if (iterB->next != NULL)
			{
				iterB = iterB->next;
			}
			else break;
		}
		if (iterA->next != NULL)
		{
			iterA = iterA->next;
		}
		else break;
	}
}
void polynomial::print()
{
	if (is_zero())
	{
		printf("0");
		return;
	}
	term* curr = this->head;
	while (true)
	{
		if (curr->coef < 0 || curr == head)
		{
			if(curr->exp == 0)
				printf("%d", curr->coef);
			else if (curr->coef == -1)
				printf("-x^%d", curr->exp);
			else printf("%dx^%d", curr->coef, curr->exp);
		}
		else
		{
			if (curr->exp == 0)
				printf("+%d", curr->coef);
			else if (curr->coef == 1)
				printf("+x^%d", curr->exp);
			else printf("+%dx^%d", curr->coef, curr->exp);
		}
		if (curr->next != NULL)
		{
			curr = curr->next;
		}
		else break;
	}
	printf("\n");
}