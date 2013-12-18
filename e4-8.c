#include <stdio.h>
#include <string.h>

/* 1文字しかプッシュバックできない getch/ungetch を作る */
/* 何のために！？ */

#define EMPTY -2

int memory = EMPTY;

int getch(void)
{
	if  (memory != EMPTY) {
		int tmp = memory;

		memory = EMPTY;
		return tmp;
	} else {
		return getchar();
	}
}

void ungetch(int c)
{
	if (memory != EMPTY)
		printf("ungetch: too many characters\n");
	else
		memory = c;
}

int main()
{
	int c, d;

	c = getch();
	ungetch(c);
	d = getch();
	if (c == d) {
		printf("OK (got '%c', pushed it back, and then got '%c')\n", c, d);
	}
	printf("pushing back two characters...\n");
	ungetch(d);
	ungetch(d);
	printf("↑ there should be an error message.\n");
	return 0;
}
