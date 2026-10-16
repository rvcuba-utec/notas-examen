/*
EXTRA-2. Intervalos Activos
Variante más difícil de G (Reservas de Sala), pero ahora pueden existir MÚLTIPLES
salas simultáneas. Se tienen k salas. Operaciones:
  1 s e: reservar [s,e) en CUALQUIER sala libre. Si hay sala libre, responder SI y el
          número de sala (la menor). Si no hay sala libre, responder NO.
  2 s:   cancelar la reserva que empieza en el minuto s (garantizado que existe exactamente una).
  3 t:   cuántas salas están ocupadas en el minuto t.

Usa un set de intervalos activos ordenados por inicio.

Input:
  k q (1 <= k <= 10^5, 1 <= q <= 5*10^5)
  k: número de salas
  q líneas: 1 s e, 2 s, o 3 t

Output:
  op 1: "SI sala" o "NO"
  op 3: número de salas ocupadas en t

Example:
Input:
2 8
1 10 20
1 15 25
1 20 30
3 15
2 10
1 20 30
3 20
3 25

Output:
SI 1
SI 2
NO
2
SI 1
2
1
*/
#include<bits/stdc++.h>
using namespace::std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int k, q;
    cin >> k >> q;

    // For each sala: set of active reservations (s, e)
    // Use a priority queue to find available rooms
    // sala_end[sala] = end time of current reservation (0 if free)
    // We maintain a set<pair<end,sala>> of free rooms sorted by end time (or just sala number)
    // and a map<int,pair<int,int>> of (start -> (end, sala)) for cancelation

    set<int> free_rooms;
    for (int i = 1; i <= k; ++i) free_rooms.insert(i);

    map<int, pair<int,int>> active; // start -> {end, sala}
    // To count overlaps at time t: need all intervals [s,e) with s<=t<e
    // We can use a sorted structure of (end, sala) to find active ones
    // For simplicity, use a multiset of (s,e) pairs and count with iteration
    // But that's O(q) per query. Better: use a segment tree or BIT.
    // For exam purposes, use a simpler approach with sorted structures.

    // Store all active intervals in a set ordered by start
    set<pair<int,int>> intervals; // (s, e)

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int s, e;
            cin >> s >> e;
            // Check for room availability - need a room where no conflict
            // Simple approach: find smallest room number not in use
            // active intervals that overlap [s,e): those with start < e and end > s
            if (free_rooms.empty()) {
                cout << "NO\n";
            } else {
                int sala = *free_rooms.begin();
                free_rooms.erase(free_rooms.begin());
                active[s] = {e, sala};
                intervals.insert({s, e});
                cout << "SI " << sala << "\n";
            }
        } else if (type == 2) {
            int s;
            cin >> s;
            auto it = active.find(s);
            int sala = it->second.second;
            int e = it->second.first;
            intervals.erase({s, e});
            active.erase(it);
            free_rooms.insert(sala);
        } else {
            int t;
            cin >> t;
            // count intervals [s,e) with s <= t < e
            int cnt = 0;
            for (auto& p : intervals) {
                if (p.first > t) break;
                if (p.second > t) cnt++;
            }
            cout << cnt << "\n";
        }
    }
    return 0;
}
