// ============================================================
// Merge Sort + Conteo de Inversiones
// ============================================================
// Complejidad: O(n log n) tiempo, O(n) espacio
//
// Uso: Ordenamiento estable. La variante con conteo de inversiones
//      es un clásico de Codeforces.
//
// Inversión: par (i, j) donde i < j y arr[i] > arr[j]
//
// Aplicaciones:
//   - Ordenamiento estable O(n log n)
//   - Contar inversiones (cuántos swaps necesita bubble sort)
//   - Base para algoritmos divide and conquer
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------
// Merge Sort clásico
// -----------------------------------------------
void merge_sort(vector<int> &arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);

    vector<int> temp;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    for (int k = 0; k < (int)temp.size(); ++k) {
        arr[left + k] = temp[k];
    }
}

// -----------------------------------------------
// Merge Sort con conteo de inversiones
// -----------------------------------------------
long long merge_count(vector<int> &arr, int left, int right) {
    if (left >= right) return 0;
    int mid = left + (right - left) / 2;
    long long inv = 0;
    inv += merge_count(arr, left, mid);
    inv += merge_count(arr, mid + 1, right);

    vector<int> temp;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i++]);
        } else {
            // Todos los restantes en la mitad izquierda son mayores que arr[j]
            inv += (mid - i + 1);
            temp.push_back(arr[j++]);
        }
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    for (int k = 0; k < (int)temp.size(); ++k) {
        arr[left + k] = temp[k];
    }
    return inv;
}

int main() {
    vector<int> arr = {5, 3, 2, 4, 1};

    // Contar inversiones
    vector<int> copy_arr = arr;
    cout << "Inversions: " << merge_count(copy_arr, 0, (int)copy_arr.size() - 1) << '\n'; // 8

    // Merge sort
    merge_sort(arr, 0, (int)arr.size() - 1);
    cout << "Sorted: ";
    for (int x : arr) cout << x << " ";
    cout << '\n';

    return 0;
}
