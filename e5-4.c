#include <stdio.h>

/* s が t で 終わっていたら 1 を返す */
int strend(char *s, char *t)
{
    for (; *s != '\0'; s++) {
        char *p = s, *q = t;

        while (*p == *q && *p != '\0' && *q != '\0') {
            p++, q++;
        }
        if (*p == '\0' && *q == '\0')
            return 1;
    }
    return 0;
}

int main()
{
    char a[80],b[80];

    while (scanf("%s%s", a, b) == 2) {
        int res;

        res = strend(a, b);
        printf("%s %s with %s\n",
               a,
               res ? "ends" : "doesn't end",
               b);
    }
    return 0;
}
