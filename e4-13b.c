#include <string.h>
#include <stdio.h>

#define SWAP(a,b) do { typeof(a) tmp; tmp = a; a = b; b = tmp; } while (0)

/* 文字列の個々の文字の位置ひとつ左にずらす。
   シフト後の文字列の長さを返す */
int left_shift(char s[])
{
    int len = strlen(s);
    int i;

    /* NUL 文字までコピーする */
    for (i=1; i <= len; ++i)
        s[i-1] = s[i];

    return len - 1;
}

void reverse(char s[])
{
    if (s[0] == '\0') return;

    char head = s[0];
    int len = left_shift(s);
    reverse(s);
    s[len] = head;

    return;
}

main()
{
    char buf[1024];

    while (gets(buf) != NULL) {
        reverse(buf);
        printf("%s\n", buf);
    }
}

