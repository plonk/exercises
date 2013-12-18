#include <stdio.h>

/*
 * 文字の頻度をヒストグラムにする
 */

void print_histogram(int occur[], int size)
{
  int i, j;

  for (i = 0; i < size; ++i) {
    if (!occur[i])
      continue;
    if (0x20 <= i && i < 0x7F) /* [SPC, DEL) */
      printf("%c %02Xh: ", i, i);
    else
      printf("  %02Xh: ", i);
      
    for (j = 0; j < occur[i]; ++j)
      putchar('*');
    putchar('\n');
  }
}

main()
{
  int c;
  int cfreq[256] = { 0 };

  while ((c = getchar()) != EOF) {
    cfreq[c]++;
  }

  /* ヒストグラムを出力しましょう */
  print_histogram(cfreq, 256);
}

