#include <stdio.h>

/* emacs も M-Space で複数の空白を1つにできるよ! */

main()
{
  int c, prev = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ' && prev == ' ')
      ;
    else
      putchar(c);
    prev = c;
  }
}
