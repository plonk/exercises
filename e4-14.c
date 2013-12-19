#include <stdio.h>

#define swap(t,x,y) do { t tmp; tmp = (x); (x) = (y); (y) = tmp; } while (0)

int main()
{
    int a, b;

    a = 10, b = 30;

    printf("a=%d, b=%d\n", a, b);
    swap(int, a, b);
    printf("a=%d, b=%d\n", a, b);
    

    return 0;
}


