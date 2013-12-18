#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);

main()
{
  int type;
  double op2;
  double tmp, tmp2;
  extern int sp;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
	push(pop() / op2);
      else
	printf("error: zero divisor\n");
      break;
    case '%':
      op2 = pop();
      push((int) pop() % (int) op2);
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    case 'p':
      tmp = pop();
      printf("\t%.8g\n", tmp);
      push(tmp);
      break;
    case 'c':
      tmp = pop();
      push(tmp); push(tmp);
      break;
    case 'x':
      tmp = pop(); tmp2 = pop();
      push(tmp); push(tmp2);
      break;
    case 'e':
      while (sp != 0)
	pop();
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
  return 0;
}

#define MAXVAL 100
int sp = 0;
double val[MAXVAL];

void push(double f)
{
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/*
 * 標準入力より次のトークンを得る。
 * s にはトークンが入り、返り値はトークンが演算子ならば
 * その文字、数字ならば '0'。
 */
int getop(char s[])
{
  int i, c;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.' && c != '-')
    return c;
  i = 0;
  if (isdigit(c) || c == '-')
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.')
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (s[0] == '-' && s[1] == '\0') {
    ungetch(c);
    return '-';
  }
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}

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

