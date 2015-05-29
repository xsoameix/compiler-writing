#include <stdio.h>

int
f(char c) { /* input precedence function */
  if (c == '|')             return 1;
  if (c == '&')             return 3;
  if (c == '!')             return 14;
  if (c == '<' || c == '>') return 6;
  if (c == '+' || c == '-') return 8;
  if (c == '*' || c == '/') return 10;
  if (c == '^')             return 13;
  if (c == '(')             return 17;
  if (c == ')' || c == 0)   return 0;
  return 15;
}

int
g(char c) { /* stack precedence function */
  if (c == '|')             return 2;
  if (c == '&')             return 4;
  if (c == '!')             return 5;
  if (c == '<' || c == '>') return 7;
  if (c == '+' || c == '-') return 9;
  if (c == '*' || c == '/') return 11;
  if (c == '^')             return 12;
  if (c == '(')             return 0;
  return 16;
}

int
h(char f, char s) { /* character-pair matrix h */
  return ((f == '|' || f == '&' || f == '!' ||
           f == '<' || f == '>' ||
           f == '+' || f == '-' || f == '*' || f == '/' || f == '^' ||
           f == '(') ^
          (s == '|' || s == '&' ||
           s == '<' || s == '>' ||
           s == '+' || s == '-' || s == '*' || s == '/' || s == '^' ||
           s == ')' || s == 0));
}

int
main(void) {
  /* stack, input and output string */
  char s[100] = {'('}, in[] = "!a<!b", out[100] = {0}, p = '(';
  int top = 1, i = 0, j = 0, len = sizeof(in) / sizeof(in[0]);
  for (; i < len && h(p, in[i]); p = in[i++])
    while (top || !(i = len - 1, top = 1))
      if (g(s[top-1]) < f(in[i])) {
        s[top++] = in[i];
        break;
      } else if (g(s[top-1]) > f(in[i])) {
        out[j++] = s[--top];
      } else {
        top--;
        break;
      }
  puts(i < len && !h(p, in[i]) ? "INVALID SYMBOL PAIR" :
       top ? "INVALID EXPRESSION" : out);
  return 0;
}
