/* detab */
#include <stdio.h>
#include <stdlib.h>

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

/* col に一番ちかいタブストップを返す */
int next_tabstop(int col)
{
    int i;

    /* col より大きい要素の中で最小のものを返す */
    for (i = 1; i < TABSTOP_MAX; ++i) {
        if (tabstop[i] > col)
            return tabstop[i];
    }
    printf("next_tabstop: line too long\n");
    return -1;
}

int main(int argc, char **argv)
{
    int c, col;

    init_tabstop(argc, argv);

    col = 0; /* 現在の桁 */
    while ((c = getchar()) != EOF)
        if (c == '\t') {
            int next = next_tabstop(col);

            if (next == -1)
                exit(1);

            int nspace = next - col;
            int i;

            for (i=0; i < nspace; ++i)
                putchar(' ');
            col = next;
        } else if (c == '\n') {
            putchar('\n');
            col = 0;
        } else {
            putchar(c);
            ++col;
        }
}
