// ============================================================
// Counting Sort + Coordinate Compression
// ============================================================
// Counting Sort: O(n + k) tiempo, O(k) espacio
// Coordinate Compression: O(n log n) tiempo, O(n) espacio
//
// Uso:
//   Counting Sort: Ordenar enteros en rango limitado.
//   Coordinate Compression: Reducir valores grandes a [0, n).
//
// Aplicaciones:
//   - Ordenar cuando el rango es acotado
//   - Frequency sort
//   - Reducir coordenadas para BIT/Segment Tree
//   - Problemas de rangos con valores hasta 1e9
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------
// Counting Sort (valores no negativos)
// -----------------------------------------------
void counting_sort(vector<int> &arr) {
    if (arr.empty()) return;
    int max_val = *max_element(arr.begin(), arr.end());
    vector<int> count(max_val + 1, 0);

    for (int x : arr) count[x]++;

    int idx = 0;
    for (int val = 0; val <= max_val; ++val) {
        while (count[val]-- > 0) arr[idx++] = val;
    }
}

// -----------------------------------------------
// Coordinate Compression
// -----------------------------------------------
// Dado un arreglo con valores grandes,
// mapear cada valor a su posición en el arreglo ordenado
// de valores únicos (rango [0, cantidad_únicos))
vector<int> coordinate_compress(vector<int> &arr) {
    // Obtener valores únicos ordenados
    vector<int> sorted_unique = arr;
    sort(sorted_unique.begin(), sorted_unique.end());
    sorted_unique.erase(unique(sorted_unique.begin(), sorted_unique.end()), sorted_unique.end());

    // Mapear cada valor a su posición
    vector<int> compressed(arr.size());
    for (int i = 0; i < (int)arr.size(); ++i) {
        compressed[i] = lower_bound(sorted_unique.begin(), sorted_unique.end(), arr[i])
                      - sorted_unique.begin();
    }

    return compressed;
}

int main() {
    // Counting Sort
    vector<int> arr = {4, 2, 2, 8, 3, 3, 1};
    counting_sort(arr);
    cout << "Counting sort: ";
    for (int x : arr) cout << x << " ";
    cout << '\n'; // 1 2 2 3 3 4 8

    // Coordinate Compression
    vector<int> arr2 = {1000000000, 1, 999999999, 1, 500000000};
    auto compressed = coordinate_compress(arr2);
    cout << "Compressed: ";
    for (int x : compressed) cout << x << " ";
    cout << '\n'; // 3 0 2 0 1

    return 0;
}
