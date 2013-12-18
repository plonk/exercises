#include <stdio.h>

void escape(const char *s, char *t)
{
  while (*s) {
    switch (*s) {
    case '\a':
      *t++ = '\\';
      *t++ = 'a';
      s++;
      break;
    case '\b':
      *t++ = '\\';
      *t++ = 'b';
      s++;
      break;
    case '\f':
      *t++ = '\\';
      *t++ = 'f';
      s++;
      break;
    case '\n':
      *t++ = '\\';
      *t++ = 'n';
      s++;
      break;
    case '\r':
      *t++ = '\\';
      *t++ = 'r';
      s++;
      break;
    case '\t':
      *t++ = '\\';
      *t++ = 't';
      s++;
      break;
    case '\v':
      *t++ = '\\';
      *t++ = 'v';
      s++;
      break;
    case '\\':
    case '\'':
    case '\"':
      *t++ = '\\';
      *t++ = *s++;
      break;
    default:
      *t++ = *s++;
      break;
    }
  }
  *t = '\0';
}

void unescape(const char *s, char *t)
{
  while (*s) {
    if (*s == '\\') {
      s++;
      switch (*s) {
      case 'a':
	*t++ = '\a';
	s++;
	break;
      case 'b':
	*t++ = '\b';
	s++;
	break;
      case 'f':
	*t++ = '\f';
	s++;
	break;
      case 'n':
	*t++ = '\n';
	s++;
	break;
      case 'r':
	*t++ = '\r';
	s++;
	break;
      case 't':
	*t++ = '\t';
	s++;
	break;
      case 'v':
	*t++ = '\v';
	s++;
	break;
      case '\\':
	*t++ = '\\';
	s++;
	break;
      case '\'':
	*t++ = '\'';
	s++;
	break;
      case '\"':
	*t++ = '\"';
	s++;
	break;
      default: /* わからないエスケープ記法 */
	*t++ = '\\';
	*t++ = *s++;
      }
    } else {
      *t++ = *s++;
    }
  }
  *t = '\0';
}

#include <string.h>

char *chop(char *s)
{
  int len = strlen(s);

  if (s[len-1] == '\n')
    s[len-1] = '\0';
  return s;
}
      

int main(int argc, char *argv[])
{
  char buf[1024 + 1];
  char dst[2048 + 1];
  void (*transform)(const char *, char *) = escape;

  if (argc == 2)
    transform = unescape;

  while (fgets(buf, sizeof buf, stdin) != NULL) {
    chop(buf);
    transform(buf, dst);
    printf("%s\n", dst);
  }
  return 0;
}
