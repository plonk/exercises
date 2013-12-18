#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
#define DEBUG_printf(args...) fprintf(stderr, args)
#else
#define DEBUG_printf(args...)
#endif

#define MAXDEPTH 10

#define NORMAL 0 
#define S_LITERAL 1
#define C_LITERAL 2
#define COMMENT 3

int peek(void);
int is_open_paren(int);
int is_close_paren(int);
int close_to_open(int paren);
int check(int paren);
int no_open_paren(void);
void print_first(char *line, int size);

char paren_stack[MAXDEPTH];
int ps_index;
int lineno = 1;

/* C プログラムの括弧の対応をチェックする */
main()
{
  int c;
  int state = NORMAL;

  while ((c = getchar()) != EOF) {
    if (c == '\n')
      lineno++;

    if (state == NORMAL) {
      if (c == '/' && peek() == '*') {
	getchar(); /* == '*' */
	state = COMMENT;
      } else if (c == '"') {
	state = S_LITERAL;
      } else if (c == '\'') {
	state = C_LITERAL;
      } else if (is_open_paren(c) || is_close_paren(c)) {
	if (!check(c)) {
	  printf("at line %d, %c with no corresponding %c\n",
		 lineno,
		 c,
		 close_to_open(c));
	  goto Error;
	}
      } else
	;
    } else if (state == S_LITERAL) {
      if (c == '\\') {
	getchar(); /* " が来ても脱出しないように読み捨てる */
      } else {
	if (c == '"')
	  state = NORMAL;
      }
    } else if (state == C_LITERAL) {
      if (c == '\\') {
	getchar(); /* ' */
      } else {
	if (c == '\'')
	  state = NORMAL;
      }
    } else if (state == COMMENT) {
      if (c == '*' && peek() == '/') {
	getchar();
	state = NORMAL;
      }
    } else {
      printf("impossible state\n");
      abort();
    }
  }
  if (no_open_paren()) {
    printf("OK\n");
    return EXIT_SUCCESS;
  }
 Error:
  printf("Syntax Error\n");
  return EXIT_FAILURE;
}

void print_first(char *line, int size)
{
  char fmt[20];

  sprintf(fmt, "%%.%ds", size);
  printf(fmt, line);
}

int no_open_paren(void)
{
  return ps_index == 0;
}

int check(int paren)
{
#ifdef DEBUG
  if (ps_index > 0) {
    print_first(paren_stack, ps_index);
    putchar('\n');
  }
#endif
  if (is_open_paren(paren)) {
    if (ps_index < MAXDEPTH) {
      paren_stack[ps_index++] = paren;
    } else {
      printf("Error: too many opening parentheses\n");
      exit(1);
    }
    DEBUG_printf("paren %c opened at line %d\n", paren, lineno);
  } else if (is_close_paren(paren)) {
    if ( ps_index > 0 &&
	 paren_stack[ps_index-1] == close_to_open(paren) ) {
      paren_stack[--ps_index];
      DEBUG_printf("paren %c closed at line %d\n", paren, lineno);
    } else {
      DEBUG_printf("could not close paren %c at line %d\n", paren, lineno);
      return 0;
    }
  }
  return 1;
}

int is_open_paren(int c)
{
  return (c=='[' || c=='(' || c=='{');
}

int is_close_paren(int c)
{
  return (c==']' || c==')' || c=='}');
}

int close_to_open(int paren)
{
  if (paren == ']')
    return '[';
  else if (paren == ')')
    return '(';
  else if (paren == '}')
    return '{';
  else
    abort();
}

/* 次の文字を覗く */
int peek()
{
  int c = getchar();
  ungetc(c, stdin);
  return c;
}

