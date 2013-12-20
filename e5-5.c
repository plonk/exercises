#include <stdio.h>
#include <string.h>

char *
my_strncpy(char *dest, const char *src, size_t n)
{
    for (; n > 0 && *src != '\0'; n--)
        *dest++ = *src++;

    if (n > 0)
        *dest = '\0';

    return dest;
}

char *
my_strncat(char *dest, const char *src, size_t n)
{
    while (*dest != '\0')
        dest++;

    for (; n > 0 && *src != '\0'; n--)
        *dest++ = *src++;

    if (n > 0)
        *dest = '\0';

    return dest;
}

int
my_strncmp(const char *s1, const char *s2, size_t n)
{
    for (; n > 0; n--, s1++, s2++) {
        int cmp = (*s1 - *s2);

        if (cmp)
            return cmp;
    }
    return 0;
}

#define BUFSIZE 1024

int main()
{
    char copybuf[BUFSIZE] = "";
    char catbuf[BUFSIZE] = "";
    char cmpbuf[] = "hello world";
    char line[BUFSIZE];

    printf("CAT BUF には 3 文字ずつ追加する。\n");

    while (gets(line) != NULL) {
        my_strncpy(copybuf, line, BUFSIZE-1);
        copybuf[BUFSIZE-1] = '\0';

        my_strncat(catbuf, line, 3);

        int res = my_strncmp(cmpbuf, line, 3);

        printf("COPY BUF: %s\n", copybuf);
        printf(" CAT BUF: %s\n", catbuf);
        printf("strncmp(\"%s\", \"%s\", 3) => %d\n", cmpbuf, line, res);
    }
}
