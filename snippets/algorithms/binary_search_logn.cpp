// ============================================================
// Binary Search - Búsqueda binaria + lower/upper bound
// ============================================================
// Complejidad: O(log n) tiempo, O(1) espacio
//
// Uso: Búsqueda eficiente en arreglos ORDENADOS.
//      También para "binary search on the answer" (búsqueda
//      binaria sobre la respuesta), muy común en Codeforces.
//
// Aplicaciones:
//   - Búsqueda en arreglo ordenado
//   - lower_bound / upper_bound (STL y manual)
//   - Binary search on the answer (encontrar el mínimo/máximo
//     valor que cumple una condición monótona)
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------
// Búsqueda binaria clásica (manual)
// -----------------------------------------------
// Retorna el índice del elemento, o -1 si no existe
int binary_search_manual(vector<int> &arr, int target) {
    int lo = 0, hi = (int)arr.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2; // Evita overflow
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

// -----------------------------------------------
// Con STL: lower_bound, upper_bound, binary_search
// -----------------------------------------------
// lower_bound(begin, end, val) → iterador al primer >= val
// upper_bound(begin, end, val) → iterador al primer > val
// binary_search(begin, end, val) → bool (existe o no)

// -----------------------------------------------
// Binary Search on the Answer
// -----------------------------------------------
// Patrón: encontrar el mínimo valor x tal que check(x) sea true,
// donde check es monótona (false, false, ..., true, true, ...)
//
// Ejemplo: dado un arreglo, ¿cuál es el mínimo valor máximo
// para dividir en k partes?

bool can_split(vector<int> &arr, int k, long long max_sum) {
    int parts = 1;
    long long current_sum = 0;
    for (int x : arr) {
        if (x > max_sum) return false;
        if (current_sum + x > max_sum) {
            ++parts;
            current_sum = x;
        } else {
            current_sum += x;
        }
    }
    return parts <= k;
}

long long min_max_split(vector<int> &arr, int k) {
    long long lo = *max_element(arr.begin(), arr.end());
    long long hi = accumulate(arr.begin(), arr.end(), 0LL);

    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (can_split(arr, k, mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

// -----------------------------------------------
// Binary Search on Answer (doubles)
// -----------------------------------------------
// Para respuestas en punto flotante, usar iteraciones fijas
// Ejemplo: encontrar raíz cuadrada de x
double sqrt_bs(double x) {
    double lo = 0, hi = max(1.0, x);
    for (int iter = 0; iter < 100; ++iter) { // ~100 iteraciones da ~30 decimales
        double mid = (lo + hi) / 2;
        if (mid * mid <= x) lo = mid;
        else hi = mid;
    }
    return lo;
}

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11, 13};

    // Manual
    cout << "Index of 7: " << binary_search_manual(arr, 7) << '\n';

    // STL
    auto it = lower_bound(arr.begin(), arr.end(), 6);
    cout << "Lower bound of 6: index " << (it - arr.begin()) << ", value " << *it << '\n';

    it = upper_bound(arr.begin(), arr.end(), 7);
    cout << "Upper bound of 7: index " << (it - arr.begin()) << '\n';

    cout << "7 exists? " << binary_search(arr.begin(), arr.end(), 7) << '\n';

    // Binary search on the answer
    vector<int> arr2 = {7, 2, 5, 10, 8};
    cout << "Min max split (k=2): " << min_max_split(arr2, 2) << '\n'; // 18

    // Sqrt
    cout << "sqrt(2) ≈ " << fixed << setprecision(10) << sqrt_bs(2) << '\n';

    return 0;
}
