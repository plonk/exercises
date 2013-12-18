#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int _getline(char line[], int maxline);
void delete_trailing_blanks(char *);


main()
{
  int len;
  char line[MAXLINE];

  while ((len = _getline(line, MAXLINE)) > 0) {
    delete_trailing_blanks(line);
    if (line[0] != '\0')
      printf("%s\n", line);
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

void delete_trailing_blanks(char *s)
{
  int end;

  if (s[0] == '\0')
    return;

  for (end=0; s[end] != '\0'; ++end)
    ;
  --end;

  while (s[end] == ' ' || s[end] == '\t' || s[end] == '\n')
    s[end--] = '\0';
}
