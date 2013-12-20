/* Exercise 5-11. タブストップを指定できる entab */
#include <stdio.h>

#define DEFAULT_TABSTOP 8
#define TABSTOP_MAX 20

static int tabstop[TABSTOP_MAX] = { 0, };

void init_tabstop(int argc, char *argv[])
{
    if (argc == 1) { /* use default tab settings */
        int i;

        for (i = 1; i < TABSTOP_MAX; ++i)
            tabstop[i] = i * DEFAULT_TABSTOP;
    } else {
        int j;

        for (j = 1; j < argc; ++j)
            tabstop[j] = atoi(argv[j]);
        /* 残りはデフォルトタブ幅の倍数で埋める */
        for (; j < TABSTOP_MAX; ++j)
            tabstop[j] =
                (tabstop[j-1] / DEFAULT_TABSTOP + 1) * DEFAULT_TABSTOP;
    }
}

int ontabstop(int col)
{
    int i;

    for (i = 0; i < TABSTOP_MAX; ++i)
        if (tabstop[i]  == col)
            return 1;
    return 0;
}

/* 空白をタブに変換する */
int main(int argc, char *argv[])
{
    int c, col, nspace;

    init_tabstop(argc, argv);

    col = 0;
    nspace = 0;

    while ((c = getchar()) != EOF) {
        /* タブストップにたどりついて、ためていた空白がある */
        if (ontabstop(col) && nspace > 0) {
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

            /* 文字だったらタブストップ未満の空白を出力し、
               文字を出力し、スペースカウントをリセットする */
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
