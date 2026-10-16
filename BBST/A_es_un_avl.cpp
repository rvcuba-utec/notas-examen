/*
A. ¿Es un AVL?
Dado un árbol binario con claves enteras, determinar si es AVL, BST (pero no AVL), o NINGUNO.
- BST: para cada nodo v, todas las claves del subárbol izq son menores y las del derecho son mayores.
- AVL: BST donde además |FB(v)| <= 1 para todo nodo v, donde FB(v) = h(izq) - h(der), h(nulo)=-1.

Input:
  t (1 <= t <= 10^4): cantidad de árboles
  Para cada árbol:
    n (1 <= n <= 2*10^5): cantidad de nodos (nodo raíz = 1)
    n líneas: k_i l_i r_i -> clave del nodo i, hijo izquierdo, hijo derecho (0 = no existe)

Output: por cada árbol: "AVL", "BST" o "NINGUNO"

Example:
Input:
3
3
10 0 0
20 2 3
30 0 0
3
10 0 2
20 0 3
30 0 0
4
50 2 3
30 0 4
70 0 0
60 0 0

Output:
AVL
BST
NINGUNO
*/
#include<bits/stdc++.h>
using namespace::std;

const int MAXN = 200005;
int K[MAXN], L[MAXN], R[MAXN];

// returns {height, min_key, max_key, is_bst, is_avl}
// height = -1 si nulo
struct Info {
    int height;
    long long mn, mx;
    bool is_bst, is_avl;
};

Info dfs(int u) {
    if (u == 0) return {-1, LLONG_MAX, LLONG_MIN, true, true};
    Info left  = dfs(L[u]);
    Info right = dfs(R[u]);

    bool bst = left.is_bst && right.is_bst;
    // left subtree max must be < K[u], right subtree min must be > K[u]
    if (L[u] != 0 && left.mx >= K[u])  bst = false;
    if (R[u] != 0 && right.mn <= K[u]) bst = false;

    int h = 1 + max(left.height, right.height);
    int fb = left.height - right.height;
    bool avl = bst && left.is_avl && right.is_avl && abs(fb) <= 1;

    long long mn = (L[u] != 0) ? left.mn : K[u];
    long long mx = (R[u] != 0) ? right.mx : K[u];

    return {h, min(mn, (long long)K[u]), max(mx, (long long)K[u]), bst, avl};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> K[i] >> L[i] >> R[i];

        Info res = dfs(1);
        if (res.is_avl) cout << "AVL\n";
        else if (res.is_bst) cout << "BST\n";
        else cout << "NINGUNO\n";
    }
    return 0;
}
