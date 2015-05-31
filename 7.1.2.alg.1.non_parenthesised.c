#include <stdio.h>

int
f(char c) { /* precedence function */
  if (c == '+' || c == '-') return 1;
  if (c == '*' || c == '/') return 2;
  if (c != 0)               return 3;
  return 0;
}

int
main(void) {
  /* input string and stack */
  char in[] = "a-b*c+d/5", s[100] = {0}, loop = 0;
  int i = 0, len = sizeof(in) / sizeof(in[0]), top = 1;
  for (; i < len; i += !loop, loop = 0)
    if (f(s[top-1]) < f(in[i])) s[top++] = in[i];
    else if (top > 1)           putchar(s[--top]), loop = 1;
  putchar('\n');
  return 0;
}
