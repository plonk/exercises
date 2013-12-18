#include <stdio.h>

/* むずかしくねwwwwwwwwwww さっきの IN OUT ステートのやりかたでやるんかな */

#define IN 1
#define OUT 0

main()
{
  int c, state, oldstate;

  oldstate = OUT;
  state = OUT;

  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t')
      state = OUT;
    else
      state = IN;

    if (oldstate == IN && state == OUT)
      putchar('\n');
    else if (state == IN)
      putchar(c);

    oldstate = state;
  }
}
