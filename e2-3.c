#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

int hex_digit_to_i(int c)
{
  int n;

  if (c >= 'A' && c <= 'F')
    n = c - 'A' + 10;
  else if (c >= 'a' && c <= 'f')
    n = c - 'a' + 10;
  else if (c >= '0' && c <= '9')
    n = c - '0';
  else {
    fprintf(stderr, "Error: %s: %c is not a hexadecimal digit\n", __FUNCTION__, c);
    exit(1);
  }
  return n;
}

int rhtoi(char s[])
{
  if (*s == '\0') {
    fprintf(stderr, "error\n");
    exit(1);
  } else if (*(s+1) == '\0') {
    return hex_digit_to_i(*s);
  } else {
    return hex_digit_to_i(*s) + 16 * rhtoi(s+1);
  }
}

/* 16 進の文字列を整数に変換する */
int htoi(char s[])
{
  if (*s == '0' && toupper(*(s+1)) == 'X')
    s += 2;

  reverse(s);
  return rhtoi(s);
}

int main()
{
  char line[100];

  while (gets(line) != NULL)
    printf("%d\n", htoi(line));
  return 0;
}
