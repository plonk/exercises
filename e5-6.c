#include <stdio.h>

int array_getline(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

int pointer_getline(char *s, int lim)
{
    char *orig_s = s;
    int c;

    for (; lim > 1 && (c=getchar()) != EOF && c != '\n'; lim--)
        *s++ = c;
    if (c == '\n')
        *s++ = '\n';
    *s = '\0';
    return s - orig_s;
}

/* 両端から交換してゆく */
void original_reverse(char s[])
{
    int left, right;
    char tmp;

    if (s[0] == '\0')
        return;

    left = 0;
    for (right=0; s[right] != '\0'; ++right)
        ;
    --right; /* 最後の文字の添字 */

    while (left < right) {
        tmp = s[left], s[left] = s[right], s[right] = tmp;
        left++, right--;
    }
}

/* 両端から交換してゆく */
void pointer_reverse(char *left)
{
    char *right;
    char tmp;

    if (*left == '\0')
        return;

    for (right=left; *right != '\0'; ++right)
        ;
    --right;

    while (left < right) {
        tmp = *left, *left = *right, *right = tmp;
        left++, right--;
    }
}

void getline_test()
{
    char buf[100];

    while (pointer_getline(buf, 100) != 0) {
        printf("%s", buf);
    }
}

int main()
{
    char buf[100];
    int len;

    while ((len = pointer_getline(buf, 100)) != 0) {
        if (buf[len-1] == '\n')
            buf[len-1] = '\0';

        pointer_reverse(buf);
        printf("%s\n", buf);
    }
    return 0;
}
