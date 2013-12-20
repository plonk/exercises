#include <stdio.h>

#include <ctype.h>

int getch(void);
void ungetch(int);

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
  return (bufp> 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

/* getint:  get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch()))    /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);    /* it's not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        int d = c;

        c = getch();

        if (!isdigit(c)) {
            ungetch(c);
            ungetch(d);
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

#define SIZE 100

int main()
{
    int n, array[SIZE], getint(int *);
    int res;

    for (n=0; n < SIZE &&
             (res = getint(&array[n])) != EOF &&
             res != 0; n++)
        ;

    int i;
    for (i = 0; i < n; ++i) {
        printf("%s%d",
               i == 0 ? "" : ", ",
               array[i]);
    }
    putchar('\n');
}
