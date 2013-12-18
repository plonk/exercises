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

void itob(int n, char s[], int base)
{
  int i, sign;
  unsigned m;
  static const char digits[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  assert(base >= 0 && base <= 36);

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
  s[i] = '\0';
  reverse(s);
}

int main(int argc, char *argv[])
{
  char buf[1024];
  int base = 10;

  if (argc > 1) {
    if (atoi(argv[1]) != 0)
      base = atoi(argv[1]);
  }

  while (fgets(buf, sizeof buf, stdin) != NULL) {
    char buf2[1024];
    int i = atoi(buf);
    itob(i, buf2, base);
    printf("%s\n", buf2);
  }
  return 0;
}
