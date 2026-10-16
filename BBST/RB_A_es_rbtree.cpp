/*
RB-A. ¿Es un árbol Red-Black?
Dado un árbol binario con claves enteras y colores (R/N), determinar si es un árbol
Red-Black válido. Propiedades:
  1. Todo nodo es ROJO o NEGRO.
  2. La raíz es NEGRA.
  3. Todo nodo ROJO tiene dos hijos NEGROS (o nulos, que se consideran NEGROS).
  4. Para todo nodo v, todos los caminos de v a una hoja descendiente tienen el mismo
     número de nodos NEGROS (black-height). Las hojas nulas cuentan como NEGRAS.
  5. Además debe ser un BST válido.

Input:
  t (1 <= t <= 10^4): cantidad de árboles
  Para cada árbol:
    n (1 <= n <= 2*10^5): cantidad de nodos (raíz = nodo 1)
    n líneas: k_i c_i l_i r_i
      k_i: clave del nodo i
      c_i: color ('R'=rojo, 'N'=negro)
      l_i r_i: hijos izq y der (0 = nulo)

Output: por cada árbol: "SI" si es RB válido, "NO" si no.

Example:
Input:
4
3
20 N 2 3
10 N 0 0
30 N 0 0
3
20 R 2 3
10 N 0 0
30 N 0 0
4
20 N 2 3
10 R 0 0
30 R 4 0
25 R 0 0
5
20 N 2 3
10 N 4 0
30 N 5 0
5 R 0 0
25 R 0 0

Output:
SI
NO
NO
SI
*/
#include<bits/stdc++.h>
using namespace::std;

const int MAXN = 200005;
int K[MAXN], L[MAXN], R[MAXN];
char C[MAXN];

// returns {black_height, is_bst, is_rb}
// black_height = -1 if invalid
struct Info {
    int bh;
    bool ok;
    long long mn, mx;
};

Info dfs(int u) {
    if (u == 0) return {0, true, LLONG_MAX, LLONG_MIN};
    Info left  = dfs(L[u]);
    Info right = dfs(R[u]);

    if (!left.ok || !right.ok) return {-1, false, 0, 0};

    // BST check
    bool bst = true;
    if (L[u] != 0 && left.mx >= K[u])  bst = false;
    if (R[u] != 0 && right.mn <= K[u]) bst = false;
    if (!bst) return {-1, false, 0, 0};

    // Property 3: red node must have black children
    if (C[u] == 'R') {
        if (L[u] != 0 && C[L[u]] == 'R') return {-1, false, 0, 0};
        if (R[u] != 0 && C[R[u]] == 'R') return {-1, false, 0, 0};
    }

    // Property 4: equal black heights
    if (left.bh != right.bh) return {-1, false, 0, 0};

    int bh = left.bh + (C[u] == 'N' ? 1 : 0);

    long long mn = (L[u] != 0) ? left.mn : K[u];
    long long mx = (R[u] != 0) ? right.mx : K[u];
    mn = min(mn, (long long)K[u]);
    mx = max(mx, (long long)K[u]);

    return {bh, true, mn, mx};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> K[i] >> C[i] >> L[i] >> R[i];

        // Property 2: root must be black
        if (C[1] != 'N') { cout << "NO\n"; continue; }

        Info res = dfs(1);
        cout << (res.ok && res.bh >= 0 ? "SI" : "NO") << "\n";
    }
    return 0;
}
