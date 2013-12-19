#include <string.h>
#include <stdio.h>

#define SWAP(a,b) do { typeof(a) tmp; tmp = a; a = b; b = tmp; } while (0)

void imp_reverse(char s[], int left, int right)
{
    if (left < right) {
        SWAP(s[left], s[right]);
        imp_reverse(s, left + 1, right - 1);
    }
    return;
}

void reverse(char s[])
{
    imp_reverse(s, 0, strlen(s) - 1);
}

int
main()
{
    char buf[1024];

    while (gets(buf) != NULL) {
        reverse(buf);
        printf("%s\n", buf);
    }
}

