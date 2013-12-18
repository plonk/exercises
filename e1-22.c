#include <stdio.h>

#define TABSTOP 8

int next_tabstop(int);
int is_space(int);

int is_space(int c)
{
  return (c == ' ' || c == '\t' || c == '\n');
}

int next_tabstop(int col)
{
  return (col/TABSTOP + 1) * TABSTOP;
}

void print_first(char *line, int size)
{
  char fmt[20];

  sprintf(fmt, "%%.%ds", size);
  printf(fmt, line);
}

void print_to_last_nonblank(char *line, int size)
{
  if (size == 0)
    return;

  while (is_space(line[--size]))
    ;

  print_first(line, size+1);
}

/* 行をある桁で折り返す */
int main()
{
  int COLS = 30;
  int c, col;

  char buf[1000];
  int i = 0;

  col = 0;

  while ((c = getchar()) != EOF) {
    if (c == '\t')
      col = next_tabstop(col);
    else
      ++col;

    buf[i++] = c;
    if (col == COLS) {
      print_to_last_nonblank(buf, i);
      putchar('\n');
      col = 0;
      i = 0;
    }
    if (c == '\n') {
      print_first(buf, i);
      col = 0;
      i = 0;
    }
  }
  return 0;
}
