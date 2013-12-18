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

unsigned rightrot(unsigned x, int n)
{
  unsigned lower;
  
  lower = getbits(x, n-1, n);
  x >>= n;
  return lower << (sizeof(unsigned)*8-n) | x;
}

int main()
{
  char buf[80];
  unsigned x;

  printf("%x\n", rightrot(0x1234abcd, 8));
  // abcd1234
  
}

