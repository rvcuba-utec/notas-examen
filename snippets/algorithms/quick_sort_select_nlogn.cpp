// ============================================================
// Quick Sort (in-place) + Quick Select (k-ésimo menor)
// ============================================================
// Quick Sort: O(n log n) promedio, O(n²) peor caso
// Quick Select: O(n) promedio, O(n²) peor caso
//
// Uso:
//   Quick Sort: Ordenamiento in-place eficiente
//   Quick Select: Encontrar el k-ésimo menor sin ordenar todo
//
// Aplicaciones:
//   - Ordenamiento general
//   - Mediana en O(n) promedio
//   - Top-K elements
//   - Partición de Lomuto / Hoare
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------
// Partición de Lomuto
// -----------------------------------------------
int lomuto_partition(vector<int> &arr, int left, int right) {
    int pivot = arr[right];
    int i = left;
    for (int j = left; j < right; ++j) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            ++i;
        }
    }
    swap(arr[i], arr[right]);
    return i;
}

// -----------------------------------------------
// Partición de Hoare (más eficiente en la práctica)
// -----------------------------------------------
int hoare_partition(vector<int> &arr, int left, int right) {
    int pivot = arr[left + (right - left) / 2];
    int i = left - 1, j = right + 1;
    while (true) {
        do { ++i; } while (arr[i] < pivot);
        do { --j; } while (arr[j] > pivot);
        if (i >= j) return j;
        swap(arr[i], arr[j]);
    }
}

// -----------------------------------------------
// Quick Sort
// -----------------------------------------------
void quick_sort(vector<int> &arr, int left, int right) {
    if (left >= right) return;
    int p = lomuto_partition(arr, left, right);
    quick_sort(arr, left, p - 1);
    quick_sort(arr, p + 1, right);
}

// -----------------------------------------------
// Quick Select: k-ésimo menor (0-indexed)
// -----------------------------------------------
int quick_select(vector<int> &arr, int left, int right, int k) {
    if (left == right) return arr[left];
    int p = lomuto_partition(arr, left, right);
    if (k == p) return arr[k];
    else if (k < p) return quick_select(arr, left, p - 1, k);
    else return quick_select(arr, p + 1, right, k);
}

int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5};
    quick_sort(arr, 0, (int)arr.size() - 1);
    cout << "Sorted: ";
    for (int x : arr) cout << x << " ";
    cout << '\n';

    vector<int> arr2 = {10, 7, 8, 9, 1, 5};
    cout << "3rd smallest: " << quick_select(arr2, 0, 5, 2) << '\n';

    // STL alternative: nth_element
    vector<int> arr3 = {10, 7, 8, 9, 1, 5};
    nth_element(arr3.begin(), arr3.begin() + 2, arr3.end());
    cout << "3rd smallest (STL): " << arr3[2] << '\n';

    return 0;
}
