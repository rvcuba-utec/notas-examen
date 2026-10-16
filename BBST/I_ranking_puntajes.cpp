/*
I. Ranking de Puntajes
Torneo online, puntajes distintos, van llegando uno por uno.
q operaciones sobre un registro inicialmente vacío:
  1 x: registrar el puntaje x (garantizado: x no estaba registrado).
  2 x: responder cuántos puntajes registrados son estrictamente menores que x.
       x puede estar o no registrado.

Input:
  q (1 <= q <= 5*10^5)
  q líneas: t x con t en {1,2}, -10^9 <= x <= 10^9

Output: por cada tipo 2: cantidad de puntajes estrictamente menores que x.

Example:
Input:
8
1 50
1 20
2 30
1 80
2 80
2 81
1 10
2 5

Output:
1
2
3
0
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
        int t, x;
        cin >> t >> x;
        if (t == 1) {
            st.insert(x);
        } else {
            // order_of_key(x) = number of elements strictly less than x
            cout << (int)st.order_of_key(x) << "\n";
        }
    }
    return 0;
}
