/*
J. K-ésimo menor
Biblioteca con libros identificados por código entero. q operaciones:
  1 x: llega el libro con código x (garantizado: no hay libro disponible con código x).
  2 x: sale prestado el libro con código x (garantizado: está disponible).
  3 k: responder cuál es el k-ésimo menor código entre los libros disponibles.
       (garantizado: k está entre 1 y la cantidad de libros disponibles)

Input:
  q (2 <= q <= 5*10^5)
  q líneas: t y con t en {1,2,3}
    si t=1 o t=2: y=x es un código con -10^9 <= x <= 10^9
    si t=3: y=k con k >= 1

Output: por cada tipo 3: el k-ésimo menor código.

Example:
Input:
7
1 30
1 10
1 20
3 2
2 20
3 2
3 1

Output:
20
30
10
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ordered_set st;

    int q;
    cin >> q;
    while (q--) {
        int t, y;
        cin >> t >> y;
        if (t == 1) {
            st.insert(y);
        } else if (t == 2) {
            st.erase(y);
        } else {
            // find_by_order(k-1) gives the k-th smallest (0-indexed)
            cout << *st.find_by_order(y - 1) << "\n";
        }
    }
    return 0;
}
