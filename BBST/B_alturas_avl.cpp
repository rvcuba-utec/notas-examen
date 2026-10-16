/*
B. Alturas en un AVL
Dado n, encontrar la MENOR y MAYOR altura posible de un AVL con exactamente n nodos.
- Altura = número de aristas en el camino más largo desde la raíz hasta una hoja.
- Un nodo solo tiene altura 0.
- h(nulo) = -1.

Idea:
- Menor altura: árbol completo o casi completo -> mínima altura es ceil(log2(n+1)) - 1
  Equivalente: menor h tal que 2^(h+1) - 1 >= n, es decir h = floor(log2(n)).
  Más preciso: la menor altura h donde caben n nodos es floor(log2(n)).

- Mayor altura: árbol de Fibonacci (mínimo número de nodos para altura h).
  N(h) = mínimo nodos para AVL de altura h.
  N(-1) = 0, N(0) = 1, N(h) = 1 + N(h-1) + N(h-2).
  La mayor altura es el mayor h tal que N(h) <= n.

Nota: n puede ser hasta 10^18, así que usamos __int128 o notamos que N(h) crece como Fibonacci
y desborda rápido (~86 niveles cabe en long long).

Input:
  t (1 <= t <= 10^5): consultas
  Cada línea: n (1 <= n <= 10^18)

Output: por consulta: menor_altura mayor_altura

Example:
Input:
6
1
2
7
11
12
100000000000000000

Output:
0 0
1 1
2 3
3 3
3 4
59 84
*/
#include<bits/stdc++.h>
using namespace::std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

// N(h) = min nodes for AVL of height h
// precompute until overflow
vector<lll> minNodes;

void precompute() {
    minNodes.push_back(0);  // N(-1) = 0
    minNodes.push_back(1);  // N(0) = 1
    // index i corresponds to height i-1, so minNodes[i] = N(i-1)
    // Actually let's index: mn[h+1] = N(h), mn[0]=N(-1)=0, mn[1]=N(0)=1
    lll limit = (lll)1e18 + 5;
    while (true) {
        lll next = 1 + minNodes[minNodes.size()-1] + minNodes[minNodes.size()-2];
        if (next > limit) { minNodes.push_back(next); break; }
        minNodes.push_back(next);
    }
    // minNodes[i] = N(i-1), so N(h) = minNodes[h+1]
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    precompute();

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;

        // Min height: floor(log2(n))
        int min_h = 0;
        while ((1LL << (min_h + 1)) - 1 < n) min_h++;
        // min_h is the smallest h such that 2^(h+1)-1 >= n
        // which is floor(log2(n))

        // Max height: largest h such that N(h) <= n
        // N(h) = minNodes[h+1]
        int max_h = 0;
        for (int h = 0; h + 1 < (int)minNodes.size(); h++) {
            if (minNodes[h+1] <= (lll)n) max_h = h;
            else break;
        }

        cout << min_h << " " << max_h << "\n";
    }
    return 0;
}
