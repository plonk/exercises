#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

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

void itoa(int n, char s[], int width)
{
  int i, sign;
  unsigned m;
  static const char digits[] = "0123456789";
  const int base = 10;

  if ((sign = n) < 0)	/* 符号を記憶する */
    m = -n;		/* n を正の数にする
			   なぜ動くのか？ */
  else
    m = n;

  i = 0;
  do {	/* 数字を逆順で生成する */
    s[i++] = digits[m % base]; /* 次の数字 */
  } while ((m /= base) > 0); /* 数字を削除する */
  if (sign < 0)
    s[i++] = '-';
  while (i < width)
    s[i++] = ' ';
  s[i] = '\0';
  reverse(s);
}

int main(int argc, char *argv[])
{
  char buf[1024];
  int ary[] = { 3, 5, 10, 1024, 9999, INT_MAX, -1 };
  int i;

  printf("|---| <- MINIMUM FIELD WIDTH\n");
  for (i = 0; ary[i] != -1; ++i) {
    itoa(ary[i], buf, 5);
    printf("%s\n", buf);
  }  

  return 0;
}
