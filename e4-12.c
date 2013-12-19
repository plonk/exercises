#include <stdio.h>

/* printd の再帰のアイデアを利用した itoa */
int itoa(int n, char s[])
{
    unsigned m;
    int i = 0;

    if (n < 0) {
        m = -n;
        s[i++] = '-';
    } else {
        m = n;
    }

    if (m / 10)
        i += itoa(m / 10, s + i);
    s[i++] = m % 10 + '0';
    s[i] = '\0';
    return i;
}

int
main()
{
    int ary[] = { 1, 2, 5, 10, 100, 9999, -1, -9999 };
    int i;
    /* int の文字列化に十分な領域を確保する。 */
    char number[ 3 * sizeof(int) + 2 ];

    for (i = 0; i < sizeof(ary)/sizeof(ary[0]); ++i) {
        itoa(ary[i], number);
        printf("%s\n", number);
    }
    return 0;
}
