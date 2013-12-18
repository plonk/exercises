#include <stdio.h>
#include <string.h>

#define BUFSIZE 100
int buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp> 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

int main()
{
  ungetch(EOF);
  ungetch(EOF);
  ungetch(EOF);
  printf("got: %d\n", getch());
  printf("got: %d\n", getch());
  printf("got: %d\n", getch());
  printf("should get whatever you typed in: '%c'\n", getch());
}
