/*
H. La Moda en Vivo
Votos para canciones (identificadas por número entero). q operaciones:
  1 x: llega un voto para la canción x.
  2 x: se retira UN voto de la canción x (garantizado: tiene al menos 1 voto).
  3:   responder qué canción tiene más votos. Si empate, la de menor número.
       Imprimir: número_canción cantidad_votos.

Idea: mantener un map<int,int> votos[cancion], y un set<pair<int,int>> ordenado por
(-votos, cancion) para encontrar el máximo eficientemente.

Input:
  q (2 <= q <= 5*10^5)
  q líneas: 1 x, 2 x, o 3 (con 1 <= x <= 10^9)

Output: por cada tipo 3: cancion votos

Example:
Input:
11
1 7
1 4
1 7
3
1 4
3
2 4
3
2 7
2 7
3

Output:
7 2
4 2
7 2
4 1
*/
#include<bits/stdc++.h>
using namespace::std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    map<int,int> cnt;
    // set ordered by (-votes, song) to get max votes, min song on ties
    set<pair<int,int>> st;

    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int x;
            cin >> x;
            if (cnt.count(x)) st.erase({-cnt[x], x});
            cnt[x]++;
            st.insert({-cnt[x], x});
        } else if (type == 2) {
            int x;
            cin >> x;
            st.erase({-cnt[x], x});
            cnt[x]--;
            if (cnt[x] == 0) cnt.erase(x);
            else st.insert({-cnt[x], x});
        } else {
            auto it = st.begin();
            cout << it->second << " " << -it->first << "\n";
        }
    }
    return 0;
}
