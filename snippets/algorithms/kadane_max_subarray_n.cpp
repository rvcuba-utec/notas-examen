// ============================================================
// Kadane's Algorithm - Máxima suma de subarreglo contiguo
// ============================================================
// Complejidad: O(n) tiempo, O(1) espacio
//
// Uso: Dado un arreglo de enteros (pueden ser negativos),
//      encontrar el subarreglo contiguo con la mayor suma.
//
// Aplicaciones:
//   - Máxima ganancia en una secuencia de ganancias/pérdidas
//   - Máximo subarray en problemas de Codeforces
//   - Base para variantes 2D (máxima submatriz)
//
// Ejemplo: [-2, 1, -3, 4, -1, 2, 1, -5, 4] → Respuesta: 6
//          (subarreglo [4, -1, 2, 1])
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// Retorna la suma máxima del subarreglo contiguo
int kadane(vector<int> &arr) {
    int max_ending_here = 0;
    int max_so_far = INT_MIN; // Para manejar arreglos con todos negativos

    for (int i = 0; i < (int)arr.size(); ++i) {
        max_ending_here += arr[i];
        max_so_far = max(max_so_far, max_ending_here);
        if (max_ending_here < 0) {
            max_ending_here = 0;
        }
    }
    return max_so_far;
}

// Variante que también retorna los índices del subarreglo
tuple<int, int, int> kadane_with_indices(vector<int> &arr) {
    int max_ending_here = 0;
    int max_so_far = INT_MIN;
    int temp_start = 0;
    int start = 0, end = 0;

    for (int i = 0; i < (int)arr.size(); ++i) {
        max_ending_here += arr[i];
        if (max_ending_here > max_so_far) {
            max_so_far = max_ending_here;
            start = temp_start;
            end = i;
        }
        if (max_ending_here < 0) {
            max_ending_here = 0;
            temp_start = i + 1;
        }
    }
    return {max_so_far, start, end};
}

int main() {
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    cout << "Max subarray sum: " << kadane(arr) << '\n';

    auto [sum, s, e] = kadane_with_indices(arr);
    cout << "Sum: " << sum << " from index " << s << " to " << e << '\n';

    return 0;
}
