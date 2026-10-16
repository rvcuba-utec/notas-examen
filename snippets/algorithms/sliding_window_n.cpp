// ============================================================
// Sliding Window - Ventana deslizante (tamaño fijo y variable)
// ============================================================
// Complejidad: O(n) tiempo, O(1) espacio (o O(k) si se usa deque)
//
// Uso: Problemas donde se necesita evaluar subarreglos contiguos
//      de manera eficiente sin recalcular todo.
//
// Variante 1 (Fija): Máxima/mínima suma de k elementos contiguos
// Variante 2 (Variable): Subarreglo más corto con suma >= target
// Variante 3 (Variable): Substring más largo sin caracteres repetidos
//
// Aplicaciones:
//   - Máx/mín promedio de k elementos contiguos
//   - Substring sin caracteres repetidos (variable)
//   - Subarreglo con suma exacta / >= / <= un valor
//   - Contar subarreglos que cumplen cierta propiedad
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------
// VENTANA FIJA: Máxima suma de k elementos contiguos
// -----------------------------------------------
int max_sum_fixed_window(vector<int> &arr, int k) {
    int n = arr.size();
    int window_sum = 0;
    for (int i = 0; i < k; ++i) {
        window_sum += arr[i];
    }

    int max_sum = window_sum;

    // Deslizar la ventana: agregar el nuevo, quitar el viejo
    for (int i = k; i < n; ++i) {
        window_sum += arr[i] - arr[i - k];
        max_sum = max(max_sum, window_sum);
    }

    return max_sum;
}

// -----------------------------------------------
// VENTANA VARIABLE: Subarreglo más corto con suma >= target
// -----------------------------------------------
// Asume valores no negativos en el arreglo
int min_length_subarray_sum(vector<int> &arr, int target) {
    int n = arr.size();
    int left = 0;
    int current_sum = 0;
    int min_len = INT_MAX;

    for (int right = 0; right < n; ++right) {
        current_sum += arr[right];

        // Contraer ventana desde la izquierda mientras la suma sea suficiente
        while (current_sum >= target) {
            min_len = min(min_len, right - left + 1);
            current_sum -= arr[left];
            ++left;
        }
    }

    return (min_len == INT_MAX) ? -1 : min_len;
}

// -----------------------------------------------
// VENTANA VARIABLE: Substring más largo sin caracteres repetidos
// -----------------------------------------------
int longest_unique_substring(string &s) {
    int n = s.size();
    unordered_map<char, int> freq;
    int left = 0;
    int max_len = 0;

    for (int right = 0; right < n; ++right) {
        freq[s[right]]++;

        while (freq[s[right]] > 1) {
            freq[s[left]]--;
            ++left;
        }

        max_len = max(max_len, right - left + 1);
    }

    return max_len;
}

// -----------------------------------------------
// VENTANA FIJA: Máximo en ventana de tamaño k (Sliding Window Maximum)
// -----------------------------------------------
// Usa deque para mantener candidatos a máximo
vector<int> sliding_window_maximum(vector<int> &arr, int k) {
    int n = arr.size();
    deque<int> dq; // Almacena índices, en orden decreciente de valor
    vector<int> result;

    for (int i = 0; i < n; ++i) {
        // Quitar elementos fuera de la ventana
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        // Mantener decreciente: quitar menores o iguales al actual
        while (!dq.empty() && arr[dq.back()] <= arr[i]) {
            dq.pop_back();
        }
        dq.push_back(i);

        // A partir de la primera ventana completa, guardar resultado
        if (i >= k - 1) {
            result.push_back(arr[dq.front()]);
        }
    }

    return result;
}

int main() {
    // Ventana fija
    vector<int> arr1 = {1, 4, 2, 10, 2, 3, 1, 0, 20};
    cout << "Max sum of 4 elements: " << max_sum_fixed_window(arr1, 4) << '\n';

    // Ventana variable (suma)
    vector<int> arr2 = {2, 3, 1, 2, 4, 3};
    cout << "Min length with sum >= 7: " << min_length_subarray_sum(arr2, 7) << '\n';

    // Ventana variable (substring)
    string s = "abcabcbb";
    cout << "Longest unique substring: " << longest_unique_substring(s) << '\n';

    // Sliding Window Maximum
    vector<int> arr3 = {1, 3, -1, -3, 5, 3, 6, 7};
    auto maxs = sliding_window_maximum(arr3, 3);
    cout << "Sliding window max (k=3): ";
    for (int x : maxs) cout << x << " ";
    cout << '\n'; // 3 3 5 5 6 7

    return 0;
}
