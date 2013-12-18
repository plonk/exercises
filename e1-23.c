#include <stdio.h>
#include <stdlib.h>

#define OUT 0 
#define LITERAL 1
#define COMMENT 2

int peek();

/* 次の文字を覗く */
int peek()
{
  int c = getchar();
  ungetc(c, stdin);
  return c;
}

/* C プログラムからコメントを削除する */
main()
{
  int c, state;

  state = OUT;

  while ((c = getchar()) != EOF) {
    if (state == OUT) {
      if (c == '/' && peek() == '*') {
	getchar(); /* == '*' */
	state = COMMENT;
      } else if (c == '"') {
	putchar(c);
	state = LITERAL;
      } else {
	putchar(c);
      }
    } else if (state == LITERAL) {
      if (c == '\\')
	putchar(c), putchar(getchar());
      else {
	putchar(c);
	if (c == '"')
	  state = OUT;
      }
    } else if (state == COMMENT) {
      if (c == '*' && peek() == '/') {
	getchar();
	state = OUT;
      }
    } else {
      printf("impossible state");
      abort();
    }
  }
}
