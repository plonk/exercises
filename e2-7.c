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

unsigned invert(unsigned x, int p, int n)
{
  unsigned n_zeroes;
  unsigned mask;

  if (n < sizeof(unsigned)*8)
    n_zeroes = ~0 << n;
  else
    n_zeroes = 0;
  mask = ~(n_zeroes) << p + 1 - n;
  return x ^ mask;
}

int main()
{
  char buf[80];
  unsigned x;
  
  // 1010 1010 1010 1010 1010 1010 1010 1010
  x = invert(0xaaaaaaaa, 11, 4);
  uint_to_binary(buf, x);
  printf("%s\n", buf);
  // 1010 1010 1010 1010 1010 0101 1010 1010
  printf("0x%x\n", x);
  // aaaaa5aa

  x = invert(0xaaaaaaaa, 31, 32);
  printf("0x%x\n", x);
}

