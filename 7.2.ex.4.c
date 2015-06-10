#include <ctype.h>
#include <stdio.h>
#include <string.h>

int
N(char c) { /* is nonterminal ? */
  return isupper(c);
}

int
T(char c) { /* is terminal ? */
  return c != ':' && c != '|' && c != '\n' && c && !N(c);
}

int          /* g: grammer, n: nonterminals, t: terminals, p: symbol pairs   */
main(void) { /* s: stack, v: traversed, b: begin, e: end, m: nonterminal map */
  char g[] = "E:T|E-T\nT:F|T*F\nF:P|!P\nP:i|(E)", * n[10] = {0}, t[10],
       l = sizeof(g) - 1, * p[10], * s[10] = {g}, * m[128] = {0}, x, y, * o,
       v[128] = {0}, b[128][10] = {0}, e[128][10] = {0}, u[10][10] = {0};
  int i = 0, nl = 0, tl = 0, pl = 0, sl = 1, bl = 0, el = 0;
  while (i < l || (i = 0)) T(g[i]) && (t[tl++] = g[i]), /* set n and t */
    N(g[i]) && g[i+1] == ':' && (m[g[i]] = n[nl++] = &g[i]), i++;
  while (++i < l || (i = 0)) (T(g[i-1]) && N(g[i]) || /* set p */
                              N(g[i-1]) && T(g[i])) && (p[pl++] = g + i - 1);
  for (; i < nl; i++, s[0] = n[i], sl = 1, bl = el = 0, memset(v, 0, sizeof(v)))
    while (sl--) for (o = s[sl]; x = o[0], y = o[1], v[x] = 1, !iscntrl(x); )
      ((x == ':' || x == '|') && (N(y) && !v[y] && (s[sl++] = m[y]) ||
                                  T(y) && (b[* n[i]][bl++] = y)) || /* b, e */
       (iscntrl(y) || y == '|') && (N(x) && !v[x] && (s[sl++] = m[x]) ||
                                    T(x) && (e[* n[i]][el++] = x))), o++;
  for (i = 0; i < tl; i++) v[t[i]] = i;
  for (i = 0; i < pl; i++)
    if (T(p[i][0])) for (o = b[p[i][1]]; * o; o++) u[v[p[i][0]]][v[* o]] = 1;
    else            for (o = e[p[i][0]]; * o; o++) u[v[* o]][v[p[i][1]]] = 1;
  return 0;
}
