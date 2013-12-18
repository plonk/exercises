#include <stdio.h

main()
{
  int c, zero_or_one;

  printf("EOF = %d\n", EOF);

  while (zero_or_one = ((c = getchar()) != EOF))
    printf("c = %02hhx; (c=getchar())!=EOF = %d\n", c, zero_or_one);
  printf("(c=getchar())!=EOF = %d\n", zero_or_one);
}
