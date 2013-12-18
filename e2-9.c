#include <stdio.h>
#include <time.h>

/* bitcount:  count 1 bits in x */
int slow_bitcount(unsigned x)
{
  int b;
  for (b = 0; x != 0; x >>= 1)
    if (x & 01)
      b++;
  return b;
}

int fast_bitcount(unsigned x)
{
  int b = 0;

  while (x != 0)
    x &= (x-1), b++;

  return b;
}

int popcount(unsigned i) {
  i = i - ((i >> 1) & 0x55555555);
  i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
  i = (i + (i >> 4)) & 0x0f0f0f0f;
  i = i + (i >> 8);
  i = i + (i >> 16);
  return i & 0x3f;
}

int main()
{
  int i;
  time_t t;
  int N = 200000000;
  int b;
  volatile unsigned input = 0xffffffff;

  printf("N = %d\n", N);

  t = time(NULL);
  for (i=0; i < N; ++i) {
    b = slow_bitcount(input);
  }
  printf("%d: slow_bitcount took %d seconds\n", b, time(NULL) - t);

  t = time(NULL);
  for (i=0; i < N; ++i) {
    b = fast_bitcount(input);
  }
  printf("%d: fast_bitcount took %d seconds\n", b, time(NULL) - t);

  t = time(NULL);
  for (i=0; i < N; ++i) {
    b = popcount(input);
  }
  printf("%d: popcount took %d seconds\n", b, time(NULL) - t);

}
