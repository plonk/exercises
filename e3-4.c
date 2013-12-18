#include <stdio.h>
#include <limits.h>

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

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
  int i, sign;

  if ((sign = n) < 0)	/* 符号を記憶する */
    n = -n;		/* n を正の数にする */
  i = 0;
  do {	/* 数字を逆順で生成する */
    s[i++] = n % 10 + '0'; /* 次の数字 */
  } while ((n /= 10) > 0); /* 数字を削除する */
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

void my_itoa(int n, char s[])
{
  int i, sign;
  unsigned m;

  if ((sign = n) < 0)	/* 符号を記憶する */
    m = -n;		/* n を正の数にする */
  i = 0;
  do {	/* 数字を逆順で生成する */
    s[i++] = m % 10 + '0'; /* 次の数字 */
  } while ((m /= 10) > 0); /* 数字を削除する */
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

int main()
{
  char buf[20];

  itoa(INT_MIN, buf);
  printf("itoa(%d) = \"%s\"\n", INT_MIN, buf);

  my_itoa(INT_MIN, buf);
  printf("my_itoa(%d) = \"%s\"\n", INT_MIN, buf);
}
