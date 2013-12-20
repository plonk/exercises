#include <stdio.h>
#include <math.h>
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

/* getfloat:  get next number from input into *pn */
int getfloat(double *pn)
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

    if (c == '.')
        c = getch();

    /* 小数点以下を読み込む */
    double power;
    for (power = 1; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
        power *= 10;
    }

    /* 指数があればを読み込む */
    double exp = 0.0;
    int esign = 1;
    if (c == 'e') {
        c = getch();

        esign = (c == '-') ? -1 : 1;

        if (c == '+' || c == '-')
            c = getch();

        for (exp = 0.0; isdigit(c); c = getch())
            exp = 10.0 * exp + (c - '0');
    }

    *pn = sign * *pn / power * pow(10, exp * esign);

    if (c != EOF)
        ungetch(c);
    return c;
}

#define SIZE 100

int main()
{
    int n;
    double array[SIZE];
    int res;

    for (n=0; n < SIZE &&
             (res = getfloat(&array[n])) != EOF &&
             res != 0; n++)
        ;

    int i;
    for (i = 0; i < n; ++i) {
        printf("%s%g",
               i == 0 ? "" : ", ",
               array[i]);
    }
    putchar('\n');
}
