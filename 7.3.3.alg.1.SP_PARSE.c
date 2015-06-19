#include <ctype.h>
#include <stdio.h>
#include <string.h>

int RB(char c) { return c == ':' || c == '|'; }        /* is RHS beginning ? */
int RE(char c) { return c == '|' || c == '\n' || !c; } /* is RHS ending ?    */
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

typedef struct { char * b, * e, n; } v_t;

void /* g: grammer, s: symbols, n: nonterminals, c: precedence matrix */
C(char c[11][11], v_t v[10], char m[128]) {
  static char g[] = "E:U\nU:T|U+T\nT:V\nV:F|V*F\nF:i|(E)";
  char b[10][10] = {0}, e[10][10] = {0}, l[8][2] = {0}, r[8][2] = {0},
       s[11] = {0}, * n[10], nt, * p[10], x, y, * o;
  int i = 0, j = 0, k, gl = sizeof(g), sl = 0, ll = 0, rl = 0, pl = 0, nl = 0;
  while (i < gl || (i = 0)) T(g[i]) && (s[sl++] = g[i]) || /* set s, n */
    g[i] == ':' && (s[sl++] = g[i-1], n[nl++] = g+i-1), i++;
  while (i < gl && (o = g+i) || (i = 0)) * o == ':' && (nt = o[-1]),
    RE(* o) && (v[j-1].e = o, r[rl][0] = nt, r[rl++][1] = o[-1]), /* l, r, v */
    RB(* o) && (v[j].b = o+1, v[j++].n = l[ll][0] = nt, l[ll++][1] = o[1]), i++;
  while (i <= sl || (i = 0)) m[s[i]] = i, i++; /* set m */
  warshall(m, l, b, sl, ll), warshall(m, r, e, sl, rl); /* set b(L⁺), e(R⁺) */
  while (++i < gl) S(g[i-1]) && S(g[i]) && (p[pl++] = g + i - 1); /* set p(≐) */
  for (i = 0; i < pl && (x = p[i][0], y = p[i][1], c[m[x]][m[y]] = 3); i++) {
    for (j = 0; j < sl; j++) b[m[y]][j] && (c[m[x]][j] = 2);
    for (j = 0; j < sl && (e[m[x]][j] && (c[j][m[y]] = 1), 1); j++)
      for (k = 0; k < sl; k++) e[m[x]][j] && b[m[y]][k] && (c[j][k] = 1);
  } /* set c, ⋖ = (≐)·(L⁺), ⋗ = (R⁺)ᵀ·(≐)·(L*) */
  for (i = 0; i < sl; i++) c[i][sl] = 1, c[sl][i] = 2; /* x ⋗ #, # ⋖ x */
}

char
P(char * s, char c[11][11], v_t v[10]) {
  int i = 0, l = strlen(s);
  while (v[i].b && (v[i].e - v[i].b != l || memcmp(v[i].b, s, l))) i++;
  return memset(s, 0, l), v[i].b ? v[i].n : 0;
}

int          /* i*i+i => VALID, i*i++i => INVALID */
main(void) { /* v: reverse map RHS to nonterminal, d: valid */
  char t[] = "i+i*i", s[100] = {0}, c[11][11] = {0}, m[128];
  v_t v[10] = {0}; int i = (C(c, v, m), 0), j = 0, l = sizeof(t), d = 1;
  while (!(j == 1 && s[j] == 'E' && puts("VALID") || !d && puts("INVALID")))
    if (c[m[s[j]]][m[t[i]]] > 1) s[++j] = t[i++];
    else while (c[m[s[j-1]]][m[s[j]]] == 3 || (d = s[j] = P(s+j, c, v), 0)) j--;
  return 0;
}
