#include <stdio.h>
#include <ctype.h>
#include <math.h>

/* atof:  convert string s to double */
double atof(char s[])
{
  double val, power;
  int i, sign;

  // 空白を読み飛ばす
  for (i = 0; isspace(s[i]); i++)
    ;

  // 符号を保存する。-1 か 1 をあとでかける。
  sign = (s[i] == '-') ? -1 : 1;

  // 符号を読み飛ばす
  if (s[i] == '+' || s[i] == '-')
    i++;

  // 整数部をよみとる
  for (val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');

  // 小数点がきたぞ！
  if (s[i] == '.')
    i++; // 読み飛ばせ

  // のこりの数字は小数部として読む
  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10.0;
  }

  double exp = 0.0;
  int esign = 1;

  if (s[i] == 'e') {
    i++;

    esign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
      i++;

    for (exp = 0.0; isdigit(s[i]); i++)
      exp = 10.0 * exp + (s[i] - '0');
  }
  return sign * val / power * pow(10, exp * esign);
}

int main()
{
  char buf[1024];

  while (printf("FLOATING NUMBER? "),
	 fgets(buf, sizeof buf, stdin) != NULL) {
    double result;

    result = atof(buf);
    printf("%f, %g, %e\n", result, result, result);
  }
  return 0;
}
