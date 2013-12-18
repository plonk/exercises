#include <stdio.h>

/* getbits:  get n bits from position p */
unsigned getbits(unsigned x, int p, int n)
{
  return (x >> (p+1-n)) & ~(~0 << n);
}

// setbits(0, 30, 4, ~0)
/* x の位置 p から n ビットを y の右端 n ビットで置き換えたものを返す */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
  unsigned a = ~(~(~0 << n) << p+1-n) & x;
  // unsigned b = ~(~0 << n) << p+1-n & y;
  unsigned b = (2<<n) - 1 << p+1-n & y;

  return a | b;
}

void uint_to_binary(char s[], unsigned i)
{
  unsigned mask = 0x80000000;

  while (mask != 0) {
    if (mask & i)
      *s++ = '1';
    else
      *s++ = '0';
    mask >>= 1;
  }
  *s = '\0';
}

int popcount(unsigned n)
{
  int i = 0;

  while (n != 0) {
    i += ~(~0 << 1) & n;
    n >>= 1;
  }
  return i;
}

int main()
{
  char buf[80];

#if 0
  uint_to_binary(buf, setbits(0, 30, 4, ~0));
  // 01111000000000000000000000000000
  printf("%s\n", buf);

  uint_to_binary(buf, setbits(0xffffffff, 14, 10, 0));
  // 11111111111111111000000000011111
  printf("%s\n", buf);
#endif

  printf("popcount(499) = %d\n", popcount(499));
  printf("popcount(0xff) = %d\n", popcount(0xff));
  printf("popcount(0xffffffff) = %d\n", popcount(0xffffffff));
  
}

