#include <stdio.h>

#define TABSTOP 8

main()
{
	int c, col;

	col = 0; /* 現在の桁 */
	while ((c = getchar()) != EOF)
		if (c == '\t') {
			for (int i=0; i < TABSTOP - (col % TABSTOP); ++i)
				putchar(' ');
			col = (col / TABSTOP + 1) * TABSTOP;
		} else if (c == '\n') {
			putchar('\n');
			col = 0;
		} else {
			putchar(c);
			++col;
		}
}
