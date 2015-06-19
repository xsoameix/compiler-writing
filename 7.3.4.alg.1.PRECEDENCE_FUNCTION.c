#include <ctype.h>
#include <stdio.h>
#include <string.h>

int RB(char c) { return c == ':' || c == '|'; }        /* is RHS beginning ? */
int RE(char c) { return c == '|' || c == '\n' || !c; } /* is RHS ending ?    */
int S(char c) { return c != ':' && c != '|' & c != '\n' && c; }
int N(char c) { return isupper(c); }    /* is nonterminal ? */
int T(char c) { return S(c) && !N(c); } /* is terminal ? */

void /* d: dynmamic programming */
warshall(void * d, size_t s, int l) {
  int i, j, k;
  for (k = 0; k < l; k++)
    for (i = 0; i < l; i++)
      for (j = 0; j < l; j++)
        if (((char *) d)[i*s+k] && ((char *) d)[k*s+j])
          ((char *) d)[i*s+j] = 1;
}

typedef struct { char * b, * e, n; } v_t;

void /* g: grammer, s: symbols, n: nonterminals, c: precedence matrix */
C(char c[11][11], char cf[11], char cg[11], v_t v[10], char m[128]) {
  static char g[] = "E:U\nU:T|U+T\nT:V\nV:F|V*F\nF:i|(E)"; /* t: B⁺ */
  char b[10][10] = {0}, e[10][10] = {0}, t[22][22] = {0},
       s[11] = {0}, * n[10], nt, * p[10], x, y, z = 0, * o;
  int i = 0, j = 0, k, gl = sizeof(g), sl = 0, tl = 0, pl = 0, nl = 0;
  while (i < gl || (tl = 2*sl+2, i = 0)) T(g[i]) && (s[sl++] = g[i]) ||
    g[i] == ':' && (s[sl++] = g[i-1], n[nl++] = g+i-1), i++; /* set s, n */
  while (i <= sl || (i = 0)) m[s[i]] = i, i++; /* set m */
  while (i < gl && (o = g+i) || (i = 0)) * o == ':' && (nt = o[-1]),
    RE(* o) && (v[j-1].e = o, e[m[nt]][m[o[-1]]] = 1), /* l, r, v */
    RB(* o) && (v[j].b = o+1, v[j++].n = nt, b[m[nt]][m[o[1]]] = 1), i++;
  warshall(b, sizeof(*b), sl), warshall(e, sizeof(*e), sl); /* b(L⁺), e(R⁺) */
  while (++i < gl) S(g[i-1]) && S(g[i]) && (p[pl++] = g + i - 1); /* set p(≐) */
  for (i = 0; i < pl && (x = p[i][0], y = p[i][1], c[m[x]][m[y]] = 3); i++) {
    for (j = 0; j < sl; j++) b[m[y]][j] && (c[m[x]][j] = 2);
    for (j = 0; j < sl && (e[m[x]][j] && (c[j][m[y]] = 1), 1); j++)
      for (k = 0; k < sl; k++) e[m[x]][j] && b[m[y]][k] && (c[j][k] = 1);
  } /* set c, ⋖ = (≐)·(L⁺), ⋗ = (R⁺)ᵀ·(≐)·(L*) */
  for (i = 0; i < sl; i++) c[i][sl] = 1, c[sl][i] = 2; /* x ⋗ #, # ⋖ x */
  for (i = 0; i <= sl; i++) for (j = 0; j <= sl && (x = c[i][j], 1); j++)
    t[i][sl+1+j] = x == 1 || x == 3, t[sl+1+j][i] = x == 2 || x == 3; /* t */
  for (i = 0; i < tl && (warshall(t, sizeof(*t), tl), 1); i++) t[i][i] = 1;
  for (i = 0; i <= sl && !(cf[i] = cg[i] = 0); i++) /* f, g */
    for (j = 0; j < tl; j++) cf[i] += t[i][j], cg[i] += t[sl+1+i][j];
  for (i = 0; i <= sl; i++) for (j = 0; j <= sl && (x = cf[i], y = cg[j]); j++)
    z |= (k = c[i][j]) == 1 && x <= y || k == 2 && x >= y || k == 3 && x != y;
  printf("PRECEDENCE FUNCTIONS ARE%s VALID\n", z ? " NOT" : "");
}

char
P(char * s, char c[11][11], v_t v[10]) {
  int i = 0, l = strlen(s);
  while (v[i].b && (v[i].e - v[i].b != l || memcmp(v[i].b, s, l))) i++;
  return memset(s, 0, l), v[i].b ? v[i].n : 0;
}

int          /* i*i+i => VALID, i*i++i => INVALID */
main(void) { /* v: reverse map RHS to nonterminal, d: valid */
  char t[] = "i++i", s[100] = {0}, c[11][11] = {0}, m[128], f[11], g[11];
  v_t v[10] = {0}; int i = (C(c, f, g, v, m), 0), j = 0, l = sizeof(t), d = 1;
  while (!(j == 1 && s[j] == 'E' && puts("VALID") || !d && puts("INVALID")))
    if (f[m[s[j]]] <= g[m[t[i]]]) s[++j] = t[i++];
    else while (f[m[s[j-1]]] == g[m[s[j]]] || (d = s[j] = P(s+j, c, v), 0)) j--;
  return 0;
}
