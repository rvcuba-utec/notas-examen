/*
C. Rotaciones a mano
Árbol binario con n nodos (numerados 1..n), se aplican q rotaciones:
  I x: ROTAR-IZQUIERDA en nodo x. Sea y = hijo derecho de x (garantizado que existe).
       y toma el lugar de x; x pasa a ser hijo izquierdo de y;
       el hijo izquierdo de y pasa a ser hijo derecho de x.
  D x: ROTAR-DERECHA en nodo x. Sea y = hijo izquierdo de x (garantizado que existe).
       y toma el lugar de x; x pasa a ser hijo derecho de y;
       el hijo derecho de y pasa a ser hijo izquierdo de x.

Input:
  n q (2 <= n <= 2*10^5, 1 <= q <= 2*10^5)
  n líneas: l_i r_i (hijo izq y der del nodo i, 0 si no existe)
  q líneas: tipo x

Output:
  Primera línea: nodo raíz final.
  n líneas: hijo izq y der del nodo i en el árbol final (0 si no existe).

Example:
Input:
5 3
2 3
0 0
4 5
0 0
0 0
I 1
D 1
D 3

Output:
2
0 4
0 3
1 5
0 0
0 0
*/
#include<bits/stdc++.h>
using namespace::std;

int L[200005], R[200005], par[200005];
int root_node;

void rotate_left(int x) {
    int y = R[x];
    // y's left child becomes x's right child
    R[x] = L[y];
    if (L[y] != 0) par[L[y]] = x;
    // y takes x's place
    par[y] = par[x];
    if (par[x] == 0) root_node = y;
    else if (L[par[x]] == x) L[par[x]] = y;
    else R[par[x]] = y;
    // x becomes y's left child
    L[y] = x;
    par[x] = y;
}

void rotate_right(int x) {
    int y = L[x];
    L[x] = R[y];
    if (R[y] != 0) par[R[y]] = x;
    par[y] = par[x];
    if (par[x] == 0) root_node = y;
    else if (R[par[x]] == x) R[par[x]] = y;
    else L[par[x]] = y;
    R[y] = x;
    par[x] = y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; ++i) {
        cin >> L[i] >> R[i];
        if (L[i]) par[L[i]] = i;
        if (R[i]) par[R[i]] = i;
    }

    // find root (node with no parent)
    root_node = 1;
    for (int i = 1; i <= n; ++i) {
        if (par[i] == 0) { root_node = i; break; }
    }
    // Actually the problem says raiz = nodo 1
    // But after building par[], the root is the one with par=0
    // Let's recompute: par is initially 0 for all, then set for children
    // So root is the node where par[i] remains 0
    // But we initialized par to 0 implicitly, and only set children
    // The node not appearing as any child is the root
    // Re-detect:
    vector<bool> is_child(n+1, false);
    for (int i = 1; i <= n; ++i) {
        if (L[i]) is_child[L[i]] = true;
        if (R[i]) is_child[R[i]] = true;
    }
    for (int i = 1; i <= n; ++i) {
        if (!is_child[i]) { root_node = i; break; }
    }

    for (int i = 0; i < q; ++i) {
        char type;
        int x;
        cin >> type >> x;
        if (type == 'I') rotate_left(x);
        else rotate_right(x);
    }

    cout << root_node << "\n";
    for (int i = 1; i <= n; ++i) {
        cout << L[i] << " " << R[i] << "\n";
    }
    return 0;
}
