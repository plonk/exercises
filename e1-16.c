/* 入力の中から一番長い行を出力する */
#include <stdio.h>
#define MAXLINE 1000

int _getline(char line[], int maxline);
void copy(char to[], char fom[]);

main()
{
  int len;
  int max;
  char line[MAXLINE];
  char longest[MAXLINE];

  max = 0;
  while ((len = _getline(line, MAXLINE)) > 0) {
    if (line[strlen(line)-1] != '\n') {
      char dustbin[MAXLINE];
      int tmp;

      /* EOF にあたるか、行が終わるまで読み込む */
      while (tmp = _getline(dustbin, MAXLINE)) {
	len += tmp;
	if (dustbin[strlen(dustbin)-1] == '\n')
	  break;
      }
    }

    if (len > max) {
      max = len;
      copy(longest, line);
    }
  }
  if (max > MAXLINE-1)
    printf("length %d, beggining with:\n%s\n", max, longest);
  else if (max > 0)
    printf("%s", longest);
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

void copy(char to[], char from[])
{
  int i;

  i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}
  
