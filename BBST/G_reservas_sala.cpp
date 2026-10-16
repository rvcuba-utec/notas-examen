/*
G. Reservas de Sala
Una sala de reuniones, reservas en intervalos [s, e) (desde s inclusive hasta e exclusive).
Dos reservas chocan si hay un instante donde ambas ocupan la sala.
[10,20) y [20,30) NO chocan.

q operaciones (empezando sin reservas):
  1 s e: pedir sala para [s,e). Si choca con reserva vigente -> NO, si no -> SI y se acepta.
  2 s: cancelar reserva vigente que empieza en el minuto s (garantizado que existe).
  3 t: qué reserva vigente ocupa la sala en el minuto t -> imprimir s e, o LIBRE.

Input:
  q (1 <= q <= 5*10^5)
  op 1: s e con 0 <= s < e <= 10^9
  op 2: s con 0 <= s <= 10^9
  op 3: t con 0 <= t <= 10^9

Output:
  op 1: SI o NO
  op 3: s e o LIBRE

Example:
Input:
10
1 10 20
1 20 30
1 15 25
1 5 11
3 20
3 30
2 10
1 5 11
3 10
3 11

Output:
SI
SI
NO
NO
20 30
LIBRE
SI
5 11
LIBRE
*/
#include<bits/stdc++.h>
using namespace::std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // store reservations as map: start -> end
    map<int,int> reservas;

    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int s, e;
            cin >> s >> e;
            // check if [s,e) overlaps any reservation [a,b)
            // overlap iff a < e and s < b
            // find first reservation with start < e
            auto it = reservas.lower_bound(e);
            bool clash = false;
            if (it != reservas.begin()) {
                --it;
                // it->first < e, check if it->second > s
                if (it->second > s) clash = true;
            }
            if (!clash) {
                reservas[s] = e;
                cout << "SI\n";
            } else {
                cout << "NO\n";
            }
        } else if (type == 2) {
            int s;
            cin >> s;
            reservas.erase(s);
        } else {
            int t;
            cin >> t;
            // find reservation containing t: start <= t < end
            auto it = reservas.upper_bound(t);
            if (it != reservas.begin()) {
                --it;
                if (it->second > t) {
                    cout << it->first << " " << it->second << "\n";
                } else {
                    cout << "LIBRE\n";
                }
            } else {
                cout << "LIBRE\n";
            }
        }
    }
    return 0;
}
