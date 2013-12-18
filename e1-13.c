#include <stdio.h>

/*
 * supercalifragilisticexpialidocious?
 * supercalifragilisticexpialidocious?
 * supercalifragilisticexpialidocious?
 * supercalifragilisticexpialidocious!
 */

#define MAX_WORD_LEN 1000


#define IN 1
#define OUT 0

/* どうかんがえても、語長の下限と上限を取ったほうがいいなぁ */

void print_histogram(int woccur[])
{
  int i, j;

  for (i = 0; i < MAX_WORD_LEN+1; ++i) {
    if (!woccur[i])
      continue;
    printf("%2d: ", i);
    for (j = 0; j < woccur[i]; ++j)
      putchar('*');
    putchar('\n');
  }
}

/* ぜんぶ main でするのかなぁ……。 */

main()
{
  int c, state, oldstate, letters;
  int woccur[MAX_WORD_LEN+1] = { 0 };

  oldstate = OUT;
  state = OUT;
  letters = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t')
      state = OUT;
    else
      state = IN;

    if (state == IN)
      ++letters;
    else if (oldstate == IN) { /* got out of word */
      if (letters <= MAX_WORD_LEN)
	woccur[letters]++;
      else {
	printf("Error: Cannot handle longer words than supercalifragilisticexpialidocious.\n");
	exit(1);
      }
      letters = 0;
    }
    oldstate = state;
  }

  /* ヒストグラムを出力しましょう */
  print_histogram(woccur);
}

