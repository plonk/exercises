#include <stdio.h>

double to_celsius(double fahr)
{
  return (5.0/9.0)*(fahr-32);
}

main()
{
  int fahr;

  for (fahr = 0; fahr <= 300; fahr += 20)
    printf("%3d %6.1f\n", fahr, to_celsius(fahr));
}
