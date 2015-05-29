#include <stdio.h>

#define IF   "A"
#define THEN "B"
#define ELSE "C"
#define CHAR(x) x[0]

int
f(char c) { /* input precedence function */
  if (c == '=')             return 24;
  if (c == CHAR(IF))        return 23;
  if (c == CHAR(THEN))      return 4;
  if (c == CHAR(ELSE))      return 6;
  if (c == '|')             return 7;
  if (c == '&')             return 9;
  if (c == '!')             return 22;
  if (c == '<' || c == '>') return 12;
  if (c == '+' || c == '-') return 14;
  if (c == '*' || c == '/') return 16;
  if (c == '^')             return 21;
  if (c == '%')             return 20; /* unary minus */
  if (c == '(')             return 27;
  if (c == ')' || c == 0)   return 0;
  return 25;
}

int
g(char c) { /* stack precedence function */
  if (c == '=')             return 1;
  if (c == CHAR(IF))        return 2;
  if (c == CHAR(THEN))      return 3;
  if (c == CHAR(ELSE))      return 5;
  if (c == '|')             return 8;
  if (c == '&')             return 10;
  if (c == '!')             return 11;
  if (c == '<' || c == '>') return 13;
  if (c == '+' || c == '-') return 15;
  if (c == '*' || c == '/') return 17;
  if (c == '^')             return 18;
  if (c == '%')             return 19;
  if (c == '(')             return 0;
  return 26;
}

int
h(char f, char s) { /* character-pair matrix h */
  return ((f == '=' ||
           f == CHAR(IF) || f == CHAR(THEN) || f == CHAR(ELSE) ||
           f == '|' || f == '&' || f == '!' ||
           f == '<' || f == '>' ||
           f == '+' || f == '-' || f == '*' || f == '/' || f == '^' ||
           f == '%' || f == '(') ^
          (s == '=' ||
           s == CHAR(THEN) || s == CHAR(ELSE) ||
           s == '|' || s == '&' ||
           s == '<' || s == '>' ||
           s == '+' || s == '-' || s == '*' || s == '/' || s == '^' ||
           s == ')' || s == 0));
}

int
main(void) {
  /* stack, input and output string */
  char s[100] = {'('}, in[] = IF "a<b" THEN "c=d=%" IF "e" THEN "f" ELSE "g",
       out[100] = {0}, p = '(';
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
