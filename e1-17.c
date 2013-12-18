/* 80桁超ある行を出力する */
#include <stdio.h>
#define MAXLINE 1000

int _getline(char line[], int maxline);

main()
{
  int len;
  char line[MAXLINE];

  while ((len = _getline(line, MAXLINE)) > 0) {
    if (len > 80)
      printf("%s", line);
  }

  return 0;
}

int _getline(char s[], int lim)
{
  int c, i;

  for (i=0; i<lim-1 && (c=getchar()) !=EOF && c!='\n'; ++i) /* 複雑www */
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}
