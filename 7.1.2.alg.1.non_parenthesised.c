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
  char in[] = "a-b*c+d/5", s[100] = {0};
  int i = 0, len = sizeof(in) / sizeof(in[0]), top = 1;
  while (i++ < len)
    while (1)
      if (f(s[top-1]) < f(in[i-1])) {
        s[top++] = in[i-1];
        break;
      } else if (top > 1) {
        putchar(s[--top]);
      } else {
        break;
      }
  putchar('\n');
  return 0;
}
