#include <stdio.h>

main()
{
  float fahr, celsius;
  int lower, upper, step;

  lower=0;
  upper=300;
  step=20;

  printf(" ℃ °F\n");

  celsius = lower;
  while (celsius <= upper) {
    fahr = celsius * 9.0/5.0 + 32;
    printf("%3.0f %3.0f\n", celsius, fahr);
    celsius += step;
  }
}
