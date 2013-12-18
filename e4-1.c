#include <stdio.h>
#include <string.h>

int begin_with(char s[], char t[])
{
  int i;

  for (i = 0; t[i] != '\0'; ++i)
    if (t[i] != s[i])
      return 0;

  return 1;
}

int strrindex(char s[], char t[])
{
  int tlen = strlen(t), slen = strlen(s);
  int i;

  for (i = slen - tlen; i >= 0; --i) {
    if (begin_with(&s[i], t))
      return i;
  }

  return -1;
}

int main()
{
  char buf[1024];
  char first[1024];
  char second[1024];

  while (printf("2 WORDS? "),
	 fgets(buf, sizeof buf, stdin) != NULL) {
    int result;

    sscanf(buf, "%s%s", first, second);
    result = strrindex(first, second);
    printf("strrindex(\"%s\", \"%s\") => %d\n", first, second, result);
  }
}
