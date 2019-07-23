#define _CRT_SECURE_NO_WARNINGS
#include "mapheap.h"

int main()
{
	node tmap;
	heap theap;
	FILE* fp = fopen("obama2.txt", "r+t");
	char input[64];
	tmap.init();
	while (fscanf(fp, "%s", input) != EOF) {
		if (!is_word(input))
			continue;
		tmap.insert(input);
	} //

	tmap.indorder();

	theap.init();
	int dcnt;
	hnode temp;
	while (1) {
		strcpy(input, tmap.get_data());
		dcnt = tmap.get_cnt();
		temp.set(dcnt, input);
		theap.push(temp);
		if (tmap.remove(input))
			break;
	}
	int i;
	for (i = 0; i < 2; i++) {
		temp = theap.pop();
		printf("%s (%d)\n", temp.get_data(), temp.get_cnt());
	}
	system("pause");
	return 0;
}