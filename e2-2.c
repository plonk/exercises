#include <stdio.h>

int _getline(char s[], int lim)
{
  int c, i;

  for (i=0; i < lim - 1; ++i)
    if ((c = getchar()) == EOF)
      break;
    else if (c == '\n')
      break;
    else
      s[i] = c;

  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}

int main()
{
  char s[80];

  while (_getline(s, 80) != 0)
    printf("%s", s);
}
