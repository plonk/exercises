#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

#define MAXOP 100
#define NUMBER '0'
#define IDENTIFIER 'i'
#define ERROR 'e'

int getop(char []);
void push(double);
double pop(void);
void call_func(const char *name);

typedef double (* D)(double);
typedef double (* DD)(double,double);
typedef double (* DI)(double,int);
typedef double (* DDp)(double,double*);
typedef double (* DIp)(double,int*);

typedef enum {
  S_D   = 10,
  S_DD  = 21,
  S_DI  = 22,
  S_DDp = 13,
  S_DIp = 14
} signature_t;

struct FUNC {
  char *name;
  signature_t signature;
  union {
    void *p;
    D d;
    DD dd;
    DI di;
    DDp ddp;
    DIp dip;
  } pt;
};

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
    case IDENTIFIER:
      if (s[1] == '\0') {
	switch (s[0]) {
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
	  goto FunctionCall;
	}
	goto End;
      }
    FunctionCall:
      call_func(s);
      break;
    case ERROR:
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  End:;
  }
  return 0;
}

int arity(signature_t s)
{
  return s/10;
}

void call_func(const char *name)
{
  static struct FUNC func[] = {
    {"sin", S_D, sin},
    {"cos", S_D, cos},
    {"tan", S_D, tan},
    {"asin", S_D, asin},
    {"acos", S_D, acos},
    {"atan", S_D, atan},
    {"atan2", S_DD, atan2},
    {"sinh", S_D, sinh},
    {"cosh", S_D, cosh},
    {"tanh", S_D, tanh},
    {"exp", S_D, exp},
    {"log", S_D, log},
    {"log10", S_D, log10},
    {"pow", S_DD, pow},
    {"sqrt", S_D, sqrt},
    {"ceil", S_D, ceil},
    {"floor", S_D, floor},
    {"fabs", S_D, fabs},
    {"ldexp", S_DI, ldexp},
    {"frexp", S_DIp, frexp},
    {"modf", S_DDp, modf},
    {"fmod", S_DD, fmod},
    {NULL, 0, NULL}
  };
  int i;
  double t, u;
  double ret;

  for (i = 0; func[i].name != NULL; ++i) {
    if (strcmp(func[i].name, name) == 0) {
      switch (func[i].signature) {
      case S_D:
	t = pop();
	push( ret = func[i].pt.d(t) );
	break;
      case S_DD:
	t = pop();
	u = pop();
	push( ret = func[i].pt.dd(u,t) );
	break;
      case S_DI:
	t = pop();
	u = pop();
	push( ret = func[i].pt.di(u,t) );
	break;
      case S_DDp:
	t = pop();
	push( ret = func[i].pt.ddp(t,&u) );
	push(u);
	break;
      case S_DIp:
	{
	  int n;

	  t = pop();
	  push( ret = func[i].pt.dip(t,&n) );
	  push(n);
	}
	break;
      default:
	printf("error: unknown signature\n");
	break;
      }
      if ((ret == HUGE_VAL || ret == -HUGE_VAL)
	  && errno == ERANGE) {
	printf("error: range error\n");
      }
      return;
    }
  }
  printf("error: unknown function %s\n", name);
  return;
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

  /* 空白を読みとばし、*/
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (c == EOF)
    return EOF;
  /* 最初の文字が s[0] と c に入った。 */
  if (!isdigit(c) && c != '.' && c != '-') {
    /* わからない記号か、識別子の先頭 */
    if (isalpha(c)) {
      for (i = 1; isalnum(c = getch()); ++i) 
	s[i] = c;
      if (c != EOF)
	ungetch(c);
      s[i] = '\0';
      return IDENTIFIER;
    } else if (c == '+' || c == '*' || c == '/' || c == '%' || c == '\n') {
      return c;
    } else {
      printf("error: parse error on '%c'\n", c);
      return ERROR;
    }
  }
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

