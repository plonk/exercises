#include <stdio.h>

void expand(const char *s1, char *s2)
{
  char prev = '\0';

  while (*s1) {
    if (*s1 == '-') {
      if (prev == '\0' || *(s1+1) < prev)
	goto CopyLiterally;
      else {
	char c;
	for (c = prev + 1; c <= *(s1+1); ++c)
	  *s2++ = c;
	s1++;
      }
    } else {
    CopyLiterally:
      *s2++ = *s1;
    }
    prev = *s1;
    s1++;
  }
  *s2 = '\0';
}

int main()
{
  char buf[1024];
  char dst[2048];

  while (fgets(buf, sizeof(buf), stdin) != NULL) {
    expand(buf, dst);
    printf("%s", dst);
  }
}
