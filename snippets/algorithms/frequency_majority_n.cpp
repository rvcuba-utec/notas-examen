// ============================================================
// Frequency Count + Dutch National Flag + Majority Element
// ============================================================
// Complejidad: O(n) tiempo
//
// Uso: Problemas de conteo, partición en 3 colores,
//      y encontrar el elemento mayoritario.
//
// Aplicaciones:
//   - Contar frecuencias de elementos
//   - Sort Colors (Dutch National Flag)
//   - Majority Element (Boyer-Moore Voting)
//   - Elementos que aparecen > n/3 veces
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------
// Frequency Count con map
// -----------------------------------------------
map<int, int> count_frequencies(vector<int> &arr) {
    map<int, int> freq;
    for (int x : arr) freq[x]++;
    return freq;
}

int most_frequent(vector<int> &arr) {
    auto freq = count_frequencies(arr);
    int best = arr[0], best_count = 0;
    for (auto &[val, cnt] : freq) {
        if (cnt > best_count) { best_count = cnt; best = val; }
    }
    return best;
}

// -----------------------------------------------
// Dutch National Flag (Sort Colors)
// -----------------------------------------------
// Ordena in-place arreglo con solo 3 valores (0, 1, 2) en O(n)
void dutch_national_flag(vector<int> &arr) {
    int lo = 0, mid = 0, hi = (int)arr.size() - 1;
    while (mid <= hi) {
        if (arr[mid] == 0) swap(arr[lo++], arr[mid++]);
        else if (arr[mid] == 1) ++mid;
        else swap(arr[mid], arr[hi--]);
    }
}

// -----------------------------------------------
// Boyer-Moore Voting: elemento que aparece > n/2 veces
// -----------------------------------------------
int majority_element(vector<int> &arr) {
    int candidate = arr[0], count = 1;
    for (int i = 1; i < (int)arr.size(); ++i) {
        if (arr[i] == candidate) ++count;
        else if (--count == 0) { candidate = arr[i]; count = 1; }
    }
    // Verificar
    count = 0;
    for (int x : arr) if (x == candidate) ++count;
    return (count > (int)arr.size() / 2) ? candidate : -1;
}

// -----------------------------------------------
// Elementos que aparecen > n/3 veces
// -----------------------------------------------
vector<int> majority_n3(vector<int> &arr) {
    int c1 = 0, c2 = 0, cnt1 = 0, cnt2 = 0;
    for (int x : arr) {
        if (cnt1 > 0 && x == c1) ++cnt1;
        else if (cnt2 > 0 && x == c2) ++cnt2;
        else if (cnt1 == 0) { c1 = x; cnt1 = 1; }
        else if (cnt2 == 0) { c2 = x; cnt2 = 1; }
        else { --cnt1; --cnt2; }
    }

    cnt1 = cnt2 = 0;
    for (int x : arr) {
        if (x == c1) ++cnt1;
        else if (x == c2) ++cnt2;
    }

    vector<int> result;
    if (cnt1 > (int)arr.size() / 3) result.push_back(c1);
    if (cnt2 > (int)arr.size() / 3) result.push_back(c2);
    return result;
}

int main() {
    vector<int> colors = {2, 0, 1, 2, 1, 0, 0, 2, 1};
    dutch_national_flag(colors);
    cout << "Sorted colors: ";
    for (int x : colors) cout << x << " ";
    cout << '\n'; // 0 0 0 1 1 1 2 2 2

    vector<int> arr = {3, 3, 4, 2, 3, 3, 3};
    cout << "Majority: " << majority_element(arr) << '\n'; // 3

    vector<int> arr2 = {1, 2, 1, 2, 3, 1, 2};
    auto res = majority_n3(arr2);
    cout << "Elements > n/3: ";
    for (int x : res) cout << x << " ";
    cout << '\n'; // 1 2

    return 0;
}
