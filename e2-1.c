#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <float.h>

/* 定数から char, short, int, long の範囲を表示する */
void print_ranges_constants()
{
  printf("  unsigned char  の範囲は: % 11d 〜 %11d\n", 0, UCHAR_MAX);
  printf("  unsigned short の範囲は: % 11d 〜 %11d\n", 0, USHRT_MAX);
  printf("  unsigned int   の範囲は: % 11d 〜 %11u\n", 0, UINT_MAX);
  printf("  unsigned long  の範囲は: % 11d 〜 %11lu\n", 0, ULONG_MAX);

  printf("  signed char    の範囲は: %11d 〜 %11d\n", SCHAR_MIN, SCHAR_MAX);
  printf("  signed short   の範囲は: %11d 〜 %11d\n", SHRT_MIN, SHRT_MAX);
  printf("  signed int     の範囲は: %11d 〜 %11d\n", INT_MIN, INT_MAX);
  printf("  signed long    の範囲は: %11ld 〜 %11ld\n", LONG_MIN, LONG_MAX);

  printf("  float          の範囲は: %.0f 〜 %.0f\n", -FLT_MAX, FLT_MAX);
  printf("  double         の範囲は: %.0f 〜 %.0f\n", -DBL_MAX, DBL_MAX);
}

/* 計算によって char, short, int, long の範囲を表示する */
void print_ranges_compute()
{
  unsigned char uc = -1;
  unsigned short ush = -1;
  unsigned int ui = -1;
  unsigned long ul = -1;
  int charbits = log2((int) uc + 1);

  printf("  unsigned char  の範囲は: % 11d 〜 %11u\n", 0, uc);
  printf("  unsigned short の範囲は: % 11d 〜 %11u\n", 0, ush);
  printf("  unsigned int   の範囲は: % 11d 〜 %11u\n", 0, ui);
  printf("  unsigned long  の範囲は: % 11d 〜 %11lu\n", 0, ul);

  printf("  signed char    の範囲は: %11.0f 〜 %11.0f\n",
	 -pow(2, sizeof(signed char ) * charbits - 1),
	 +pow(2, sizeof(signed char ) * charbits - 1) - 1);
  printf("  signed short   の範囲は: %11.0f 〜 %11.0f\n",
	 -pow(2, sizeof(signed short) * charbits - 1),
	 +pow(2, sizeof(signed short) * charbits - 1) - 1);
  printf("  signed int     の範囲は: %11.0f 〜 %11.0f\n",
	 -pow(2, sizeof(signed int  ) * charbits - 1),
	 +pow(2, sizeof(signed int  ) * charbits - 1) - 1);
  printf("  signed long    の範囲は: %11.0f 〜 %11.0f\n",
	 -pow(2, sizeof(signed long ) * charbits - 1),
	 +pow(2, sizeof(signed long ) * charbits - 1) - 1);
}

int main()
{
  puts("定数:");
  print_ranges_constants();
  puts("\n計算：");
  print_ranges_compute();
  return 0;
}
