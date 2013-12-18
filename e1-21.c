#include <stdio.h>

#define TABSTOP 8

/* 空白をタブに変換する */
main()
{
  int c, col, nspace;

  col = 0;
  nspace = 0;

  while ((c = getchar()) != EOF) {
    /* タブストップにたどりついて、ためていた空白がある */
    if (col % TABSTOP == 0 && nspace > 0) {
      if (nspace == 1) /* 空白1個ならタブにしない */
	putchar(' ');
      else
	putchar('\t');
      nspace = 0; /* 空白カウントをリセットする */
    }
      
    if (c == ' ') {
      /* 空白だったらカウントするだけ */
      ++nspace;
    } else {
      int i;

      /* 文字を出力する前にためていた空白を出力する */
      /* ここでタブにする必要はない */
      if (nspace > 0) {
	for (i=0; i < nspace; ++i) {
	  putchar(' ');
	}
	nspace = 0;
      }
      putchar(c);
    }
    ++col;
    /* 出力したのが改行だったら桁をリセットする */
    if (c == '\n')
      col = 0;
  }
}
