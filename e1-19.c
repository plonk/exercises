#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int _getline(char line[], int maxline);
void reverse(char *);


main()
{
  int len;
  char line[MAXLINE];

  while ((len = _getline(line, MAXLINE)) > 0) {
    int i;

    /* 反転するために改行を削除する */
    for (i=0; line[i] != '\0'; ++i)
      if (line[i] == '\n')
	line[i] = '\0';

    reverse(line);
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


/* 両端から交換してゆく */
void reverse(char s[])
{
  int left, right;
  char tmp;

  if (s[0] == '\0')
    return;

  left = 0;
  for (right=0; s[right] != '\0'; ++right)
    ;
  --right; /* 最後の文字の添字 */

  while (left < right) {
    tmp = s[left], s[left] = s[right], s[right] = tmp;
    left++, right--;
  }
}

