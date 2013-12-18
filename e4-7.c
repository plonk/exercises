#include <stdio.h>
#include <string.h>

#define BUFSIZE 100
char buf[BUFSIZE];
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

void ungets(char s[])
{
  int i;

  ungetch('\n');
  for (i = strlen(s) - 1; i >= 0; --i) {
    ungetch(s[i]);
  }
  return;
}

char *my_getline(char s[])
{
  int c;
  int i;

  i = 0;

  while ((c = getch()) != '\n' && c != EOF) {
    s[i++] = c;
  }
  if (i == 0 && c == EOF)
    return NULL;
  else {
    s[i] = '\0';
    return s;
  }
}

/* 一度でも小文字で始まるエントリーがあったら、そこからすべて出力する */
int main()
{
  char line[100];

  while (my_getline(line) != NULL) {
    puts(line);
    ungets(line);
  }
  return 0;
}
