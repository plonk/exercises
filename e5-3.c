#include <stdio.h>

#include <string.h>

void array_strcat(char s[], char t[])
{
    int i, j;

    i = j = 0;
    while (s[i] != '\0')
        i++;
    while ((s[i++] = t[j++]) != '\0')
        ;
}

/* ポインター版 */
void pointer_strcat(char *s, char *t)
{
    while (*s != '\0')
        s++;
    while ((*s = *t) != '\0')
        s++, t++;
}

int
main()
{
    char buf[1024] = "";
    char line[1024];
    int buflen = 0;

    while (fgets(line, 1024, stdin) != NULL) {
        if (strlen(line) + buflen > 1023) {
            printf("\ntext too long. bye.\n");
            return 1;
        }
        pointer_strcat(buf, line);
        buflen += strlen(line);
        printf("----buf----\n%s---end of buf----\n", buf);
    }
    printf("----buf----\n%s---end of buf----\n", buf);
    return 0;
}
