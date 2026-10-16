/*
F. Vecino más cercano
Estaciones de carga en kilómetros enteros (pueden ser negativos). q operaciones:
  1 x: inaugurar estación en km x (garantizado: no hay estación en x)
  2 x: cerrar estación en km x (garantizado: hay estación en x)
  3 x: responder en qué km está la estación más cercana a x (minimiza |y-x|).
       Si empate, la de menor km.

Input:
  q (2 <= q <= 5*10^5)
  q líneas: tipo x, con -10^9 <= x <= 10^9

Output: por cada tipo 3, imprimir el km de la estación más cercana.

Example:
Input:
9
1 10
1 20
3 14
3 15
3 20
2 10
1 -5
3 7
3 -100

Output:
10
10
20
-5
-5
*/
#include<bits/stdc++.h>
using namespace::std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    set<int> st;

    int q;
    cin >> q;
    while (q--) {
        int type, x;
        cin >> type >> x;
        if (type == 1) {
            st.insert(x);
        } else if (type == 2) {
            st.erase(x);
        } else {
            // find closest to x
            auto it = st.lower_bound(x);
            int best = INT_MAX;
            int ans = 0;
            if (it != st.end()) {
                int d = *it - x;
                if (d < best || (d == best && *it < ans)) {
                    best = d;
                    ans = *it;
                }
            }
            if (it != st.begin()) {
                --it;
                int d = x - *it;
                if (d < best || (d == best && *it < ans)) {
                    best = d;
                    ans = *it;
                }
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
