#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef class node* nptr;
class node {
	char* name;
	int nchilds;
	nptr* childs;
public:
	void init ();
	bool is_empty ();
	void set (char nname[16]);
	void insert (int n_child, char cnames[][16]);
	int get_childs (char cnames[][16], char pname[16]);
	char* get_parent (char cname[16]);
	int has_child (char cname[16]);
	int get_siblings (char siblings[][16], char cname[16]);
	void traverse();
};
int parse_str(char toks[][16], char str[256]);