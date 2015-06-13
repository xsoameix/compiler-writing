#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define L(x) (sizeof(x) / sizeof(x[0]))

int S(char c) { return c != ':' && c != '|' & c != '\n' && c; }
int N(char c) { return isupper(c); }    /* is nonterminal ? */
int T(char c) { return S(c) && !N(c); } /* is terminal ? */

void /* p: productions, d: dynmamic programming */
warshall(char m[128], char p[][2], char d[10][10], int sl, int pl) {
  int i = 0, j, k;
  while (i < pl) d[m[p[i][0]]][m[p[i][1]]] = 1, i++;
  for (k = 0; k < sl; k++)
    for (i = 0; i < sl; i++)
      for (j = 0; j < sl; j++)
        if (d[i][k] && d[k][j])
          d[i][j] = 1;
}

int          /* g: grammer, s: symbols, n: nonterminals, t: terminals   */
main(void) { /* m: map char to i, c: precedence matrix                  */
  char g[] = "E:U\nU:T|U+T\nT:V\nV:F|V*F\nF:i|(E)", s[10], n[10], t[10], m[128],
       b[10][10] = {0}, e[10][10] = {0}, l[8][2] = {0}, r[8][2] = {0}, nt,
       * p[10], c[10][10] = {0}, x, y, nl = 0, tl = 0;
  int i = 0, j, k, gl = sizeof(g), sl = 0, ll = 0, rl = 0, pl = 0;
  while (i < gl || (i = 0)) g[i] == ':' && (s[sl++] = n[nl++] = g[i-1]) ||
    T(g[i]) && (s[sl++] = t[tl++] = g[i]), i++; /* set s, n, t */
  while (i < gl || (i = 0)) g[i] == ':' && (nt = g[i-1]), /* set l, r */
    (g[i] == ':' || g[i] == '|') && (l[ll][0] = nt, l[ll++][1] = g[i+1]),
    (iscntrl(g[i]) || g[i] == '|') && (r[rl][0] = nt, r[rl++][1] = g[i-1]), i++;
  while (i < sl || (i = 0)) m[s[i]] = i, i++; /* set m */
  warshall(m, l, b, sl, ll), warshall(m, r, e, sl, rl); /* set b(L⁺), e(R⁺) */
  while (++i < gl) S(g[i-1]) && S(g[i]) && (p[pl++] = g + i - 1); /* set p(≐) */
  for (i = 0; i < pl && (x = p[i][0], y = p[i][1], c[m[x]][m[y]] = '='); i++) {
    for (j = 0; j < sl; j++) b[m[y]][j] && (c[m[x]][j] = '<');
    for (j = 0; j < sl && (e[m[x]][j] && (c[j][m[y]] = '>'), 1); j++)
      for (k = 0; k < sl; k++) e[m[x]][j] && b[m[y]][k] && (c[j][k] = '>');
  } /* set c, ⋖ = (≐)·(L⁺), ⋗ = (R⁺)ᵀ·(≐)·(L*) */
  return 0;
}
