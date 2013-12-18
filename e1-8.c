#include <stdio.h>

/* んで、これを空白とタブの数も数えるようにせよと仰せだ。 */
/* switch はまだ出てきてないから、if で書くのかな */
/* この本のスタイルによれば、ブレースは省略できるところは省略するらしい */
/* んで、変数宣言と初期化は分けるらしい */

main()
{
  int c, nl, blank, tab;

  nl = 0;
  blank = 0;
  tab = 0;

  while ((c = getchar()) != EOF)
    if (c == '\n')
      ++nl;
    else if (c == ' ')
      ++blank;
    else if (c == '\t')
      ++tab;
  printf("lines: %d\nblanks: %d\ntabs: %d\n", nl, blank, tab);
}
