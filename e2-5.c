#include <stdio.h>
#include <string.h>


int strindex(char s[], char c)
{
  char *p = s;

  while (*p != '\0') {
    if (*p == c)
      return p - s;
    p++;
  }
  return -1;
}

int any(char *s1, char *s2)
{
  char *p = s1;
  while (*p != '\0') {
    if (strindex(s2, *p) != -1)
      return p - s1;
    p++;
  }
  return -1;
}

int main()
{
  int i;
  char *accept = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  char v[][80] = { "___H_E_L_L_O", "__1,000,000" };

  printf("許容文字: %s\n", accept);

  for (i = 0; i != sizeof(v)/sizeof(v[0]); ++i) {
    int idx;

    printf("「%s」で最初の許容文字が出るのは ", v[i]);
    idx = any(v[i], accept);
    printf("[%d] の場所です\n", idx);
  }
}
