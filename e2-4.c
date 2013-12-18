#include <stdio.h>
#include <string.h>

void squeeze(char *s1, char *s2)
{
  char *p = s1;

  while (*s1 != '\0') {
    if (strchr(s2, *s1) == NULL)
      *p++ = *s1;
    s1++;
  }
  *p = '\0';
}

int main()
{
  int i;
  char *unwanted = "_,";
  char v[][80] = { "H_E_L_L_O", "1,000,000" };

  for (i = 0; i != sizeof(v)/sizeof(v[0]); ++i) {
    printf("%s -> ", v[i]);
    squeeze(v[i], unwanted);
    printf("%s\n", v[i]);
  }
}
