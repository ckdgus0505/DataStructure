#define _CRT_SECURE_NO_WARNINGS
#include "tree.h"

int main()
{
	char str[256];
	char toks[10][16];
	int n_toks;
	node root;
	FILE* fp = fopen("¡∂º±ø’¡∂.txt", "r+t");
	root.init();
	while (fgets(str, 256, fp) != NULL) {
		n_toks = parse_str(toks, str);
		root.insert(n_toks, toks);
	}
	root.traverse();
	fclose(fp);
	system("pause");
	return 0;
}