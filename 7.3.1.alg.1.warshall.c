#include <stdio.h>

#define L(x) (sizeof(x) / sizeof(x[0]))

void
warshall(char (* p)[2], int pl) {
  char s[] = "EUTVFi()", m[128], d[L(s)][L(s)] = {0};
  int i = 0, j, k, sl = L(s)-1;
  while (i < sl || (i = 0)) m[s[i]] = i++;
  while (i < pl) d[m[p[i][0]]][m[p[i][1]]] = 1, i++;
  for (k = 0; k < sl; k++)
    for (i = 0; i < sl; i++)
      for (j = 0; j < sl; j++)
        if (d[i][k] && d[k][j])
          d[i][j] = 1;
}

int
main(void) { /* p: productions, m: map char to i, d: dynmamic programming */
  char pl[][2] = {          /* first symbol of RHS */
    {'E', 'U'},             /* E -> [U]            */
    {'U', 'T'}, {'U', 'U'}, /* U -> [T] | [U] + T  */
    {'T', 'V'},             /* T -> [V]            */
    {'V', 'F'}, {'V', 'V'}, /* V -> [F] | [V] * F  */
    {'F', 'i'}, {'F', '('}  /* F -> [i] | [(] E )  */
  }, pr[][2] = {            /* last symbol of RHS  */
    {'E', 'U'},             /* E -> [U]            */
    {'U', 'T'},             /* U -> [T] | U + [T]  */
    {'T', 'V'},             /* T -> [V]            */
    {'V', 'F'},             /* V -> [F] | V * [F]  */
    {'F', 'i'}, {'F', ')'}  /* F -> [i] | ( E [)]  */
  };
  warshall(pl, L(pl)), warshall(pr, L(pr));
  return 0;
}
