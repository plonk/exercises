#include <stdio.h>

unsigned rightrot(unsigned x, int n)
{
  asm ("movb %1, %%cl; rorl %%cl, %0"
       :"=m"(x)        /* output */
       :"m"(n)         /* input */
       );       

  return x;
}


int main()
{
  char buf[80];
  unsigned x;

  printf("%x\n", rightrot(0x1234abcd, 16));
}
