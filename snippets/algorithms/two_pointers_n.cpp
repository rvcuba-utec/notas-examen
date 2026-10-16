// ============================================================
// Two Pointers - Dos punteros
// ============================================================
// Complejidad: O(n) tiempo, O(1) espacio
//
// Uso: Problemas sobre arreglos ordenados donde se buscan
//      pares o tripletas que cumplan una condición.
//
// Aplicaciones:
//   - Par con suma exacta en arreglo ordenado
//   - Tripleta con suma exacta (combinado con iteración externa)
//   - Contenedor con más agua (Container With Most Water)
//   - Mezcla de dos arreglos ordenados
//   - Eliminar duplicados in-place
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------
// Par con suma exacta en arreglo ORDENADO
// -----------------------------------------------
pair<int, int> two_sum_sorted(vector<int> &arr, int target) {
    int left = 0, right = (int)arr.size() - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target) return {left, right};
        else if (sum < target) ++left;
        else --right;
    }
    return {-1, -1}; // No encontrado
}

// -----------------------------------------------
// Container With Most Water
// -----------------------------------------------
int max_area(vector<int> &height) {
    int left = 0, right = (int)height.size() - 1;
    int max_water = 0;

    while (left < right) {
        int h = min(height[left], height[right]);
        max_water = max(max_water, h * (right - left));

        if (height[left] < height[right]) ++left;
        else --right;
    }

    return max_water;
}

// -----------------------------------------------
// Eliminar duplicados in-place en arreglo ORDENADO
// -----------------------------------------------
int remove_duplicates(vector<int> &arr) {
    if (arr.empty()) return 0;
    int slow = 0;
    for (int fast = 1; fast < (int)arr.size(); ++fast) {
        if (arr[fast] != arr[slow]) {
            arr[++slow] = arr[fast];
        }
    }
    arr.resize(slow + 1);
    return slow + 1;
}

// -----------------------------------------------
// 3Sum: encontrar todas las tripletas que suman target
// -----------------------------------------------
vector<vector<int>> three_sum(vector<int> &arr, int target) {
    sort(arr.begin(), arr.end());
    vector<vector<int>> result;
    int n = arr.size();

    for (int i = 0; i < n - 2; ++i) {
        if (i > 0 && arr[i] == arr[i - 1]) continue; // Skip duplicados

        int left = i + 1, right = n - 1;
        while (left < right) {
            int sum = arr[i] + arr[left] + arr[right];
            if (sum == target) {
                result.push_back({arr[i], arr[left], arr[right]});
                while (left < right && arr[left] == arr[left + 1]) ++left;
                while (left < right && arr[right] == arr[right - 1]) --right;
                ++left; --right;
            } else if (sum < target) {
                ++left;
            } else {
                --right;
            }
        }
    }

    return result;
}

// -----------------------------------------------
// Merge de dos arreglos ordenados
// -----------------------------------------------
vector<int> merge_sorted(vector<int> &a, vector<int> &b) {
    vector<int> result;
    int i = 0, j = 0;
    while (i < (int)a.size() && j < (int)b.size()) {
        if (a[i] <= b[j]) result.push_back(a[i++]);
        else result.push_back(b[j++]);
    }
    while (i < (int)a.size()) result.push_back(a[i++]);
    while (j < (int)b.size()) result.push_back(b[j++]);
    return result;
}

int main() {
    // Two sum sorted
    vector<int> arr = {1, 2, 3, 4, 6, 8, 9};
    auto [i, j] = two_sum_sorted(arr, 10);
    if (i != -1)
        cout << "Pair: " << arr[i] << " + " << arr[j] << " = 10\n";

    // Container with most water
    vector<int> heights = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << "Max water: " << max_area(heights) << '\n';

    // 3Sum
    vector<int> arr3 = {-1, 0, 1, 2, -1, -4};
    auto triplets = three_sum(arr3, 0);
    cout << "3Sum triplets:\n";
    for (auto &t : triplets) {
        cout << "  " << t[0] << " " << t[1] << " " << t[2] << '\n';
    }

    return 0;
}
