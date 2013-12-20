#include <stdio.h>
#include <string.h>

#define MAXLEN 1000

int _getline(char *, int);
char *alloc(int);

int _getline(char *s, int lim)
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

int readlines(char lineptr[][MAXLEN], int maxlines)
{
    int len, nlines;
    char line[MAXLEN];

    nlines = 0;
    while ((len = _getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(lineptr[nlines++], line);
        }
    return nlines;
}

void writelines(char lineptr[][MAXLEN], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

void swap(char v[][MAXLEN], int i, int j)
{
    char temp[MAXLEN];

    strcpy(temp, v[i]);
    strcpy(v[i], v[j]);
    strcpy(v[j], temp);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char v[][MAXLEN], int left, int right)
{
    int i, last;

    /* do nothing if array contains fewer than two elements */
    if (left >= right)
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

#define MAXLINES 5000

char lineptr[MAXLINES][MAXLEN];

/* sort input lines */
int main()
{
    int nlines;

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}
