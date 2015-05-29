#include <stdio.h>

int
f(char c) { /* input precedence function */
  if (c == '+' || c == '-') return 1;
  if (c == '*' || c == '/') return 3;
  if (c == '^')             return 6;
  if (c == '(')             return 9;
  if (c == ')' || c == 0)   return 0;
  return 7;
}

int
g(char c) { /* stack precedence function */
  if (c == '+' || c == '-') return 2;
  if (c == '*' || c == '/') return 4;
  if (c == '^')             return 5;
  if (c == '(')             return 0;
  return 8;
}

int
main(void) {
  /* stack, input and output string */
  char s[100] = {'('}, in[] = "(a+b)*(c-d)", out[100] = {0};
  int top = 1, i = 0, j = 0, len = sizeof(in) / sizeof(in[0]);
  while (i++ < len)
    while (1)
      if (g(s[top-1]) < f(in[i-1])) {
        s[top++] = in[i-1];
        break;
      } else if (g(s[top-1]) > f(in[i-1])) {
        out[j++] = s[--top];
      } else {
        top--;
        break;
      }
  printf("%s\n", out);
  return 0;
}
