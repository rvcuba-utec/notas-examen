// ============================================================
// Longest Increasing Subsequence (LIS)
// ============================================================
// Complejidad: O(n log n) tiempo, O(n) espacio
//
// Uso: Encontrar la subsecuencia creciente más larga.
//      NO necesita ser contigua (a diferencia del subarreglo).
//
// Aplicaciones:
//   - LIS clásico (Codeforces, ICPC)
//   - Longest non-decreasing subsequence (cambiar < por <=)
//   - Minimum number of chains to cover a sequence
//   - Box stacking, envelope nesting (variantes 2D)
//
// Ejemplo: [10, 9, 2, 5, 3, 7, 101, 18] → LIS = 4
//          (por ejemplo [2, 3, 7, 101])
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------
// LIS en O(n log n) usando "tails array"
// -----------------------------------------------
// tails[i] = el menor valor final posible de una subsecuencia
//            creciente de longitud i+1
int lis(vector<int> &arr) {
    vector<int> tails;

    for (int x : arr) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) {
            tails.push_back(x);
        } else {
            *it = x;
        }
    }

    return tails.size();
}

// -----------------------------------------------
// LIS que también recupera la subsecuencia
// -----------------------------------------------
vector<int> lis_with_sequence(vector<int> &arr) {
    int n = arr.size();
    vector<int> tails, tails_idx, parent(n);
    // tails_idx[i] = índice original del elemento en tails[i]

    for (int i = 0; i < n; ++i) {
        auto it = lower_bound(tails.begin(), tails.end(), arr[i]);
        int pos = it - tails.begin();

        if (it == tails.end()) {
            tails.push_back(arr[i]);
            tails_idx.push_back(i);
        } else {
            *it = arr[i];
            tails_idx[pos] = i;
        }
        parent[i] = (pos > 0) ? tails_idx[pos - 1] : -1;
    }

    // Reconstruir
    vector<int> result(tails.size());
    int idx = tails_idx.back();
    for (int i = (int)result.size() - 1; i >= 0; --i) {
        result[i] = arr[idx];
        idx = parent[idx];
    }

    return result;
}

// -----------------------------------------------
// Longest Non-Decreasing Subsequence
// -----------------------------------------------
// Cambio: usar upper_bound en vez de lower_bound
int lnds(vector<int> &arr) {
    vector<int> tails;
    for (int x : arr) {
        auto it = upper_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return tails.size();
}

int main() {
    vector<int> arr = {10, 9, 2, 5, 3, 7, 101, 18};

    cout << "LIS length: " << lis(arr) << '\n'; // 4

    auto seq = lis_with_sequence(arr);
    cout << "LIS: ";
    for (int x : seq) cout << x << " ";
    cout << '\n';

    vector<int> arr2 = {3, 1, 2, 2, 4};
    cout << "LNDS length: " << lnds(arr2) << '\n'; // 4 (1, 2, 2, 4)

    return 0;
}
