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
h(char f, char s) { /* character-pair matrix h */
  return ((f == '+' || f == '-' || f == '*' || f == '/' || f == '^' ||
           f == '(') ^
          (s == '+' || s == '-' || s == '*' || s == '/' || s == '^' ||
           s == ')' || s == 0));
}

int
main(void) {
  /* stack, input and output string                                 */
  /* input string examples: "(a+b)*(c-d)"  => "ab+cd-*"             */
  /*                        "(a+b))*(c-d)" => "INVALID EXPRESSION"  */
  /*                        "(a+b)*((c-d)" => "INVALID EXPRESSION"  */
  /*                        "(a+b)*(c-d-)" => "INVALID SYMBOL PAIR" */
  char s[100] = {'('}, in[] = "(a+b)*(c-d)", out[100] = {0}, p = '(', loop = 0;
  int top = 1, i = 0, j = 0, len = sizeof(in) / sizeof(in[0]);
  for (; i < len && top && h(p, in[i]); loop || (p = in[i++]), loop = 0)
    if (g(s[top-1]) < f(in[i]))      s[top++] = in[i];
    else if (g(s[top-1]) > f(in[i])) out[j++] = s[--top], loop = 1;
    else                             top--;
  puts(i < len && !h(p, in[i]) ? "INVALID SYMBOL PAIR" :
       (i < len) == (top == 0) ? "INVALID EXPRESSION" : out);
  return 0;
}
