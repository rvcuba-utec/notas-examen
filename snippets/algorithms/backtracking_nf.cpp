// ============================================================
// Backtracking: Permutaciones, Subconjuntos, N-Queens
// ============================================================
// Permutaciones: O(n! * n)
// Subconjuntos: O(2^n * n)
// N-Queens: O(n!)
//
// Uso: Generar todas las combinaciones, permutaciones o
//      soluciones que cumplan ciertas restricciones.
//
// Aplicaciones:
//   - Generar permutaciones
//   - Generar subconjuntos (power set)
//   - N-Queens, Sudoku solver
//   - Combinaciones de tamaño k
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------
// Generar todas las permutaciones
// -----------------------------------------------
vector<vector<int>> all_permutations;

void generate_permutations(vector<int> &arr, vector<int> &current, vector<bool> &used) {
    if ((int)current.size() == (int)arr.size()) {
        all_permutations.push_back(current);
        return;
    }
    for (int i = 0; i < (int)arr.size(); ++i) {
        if (!used[i]) {
            used[i] = true;
            current.push_back(arr[i]);
            generate_permutations(arr, current, used);
            current.pop_back();
            used[i] = false;
        }
    }
}

// Alternativa STL: next_permutation
// sort(arr.begin(), arr.end());
// do { ... } while (next_permutation(arr.begin(), arr.end()));

// -----------------------------------------------
// Generar todos los subconjuntos (backtracking)
// -----------------------------------------------
vector<vector<int>> all_subsets;

void generate_subsets(vector<int> &arr, int start, vector<int> &current) {
    all_subsets.push_back(current);
    for (int i = start; i < (int)arr.size(); ++i) {
        current.push_back(arr[i]);
        generate_subsets(arr, i + 1, current);
        current.pop_back();
    }
}

// Alternativa con bitmask
vector<vector<int>> subsets_bitmask(vector<int> &arr) {
    int n = arr.size();
    vector<vector<int>> result;
    for (int mask = 0; mask < (1 << n); ++mask) {
        vector<int> subset;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) subset.push_back(arr[i]);
        }
        result.push_back(subset);
    }
    return result;
}

// -----------------------------------------------
// Combinaciones de tamaño k
// -----------------------------------------------
vector<vector<int>> all_combinations;

void generate_combinations(vector<int> &arr, int k, int start, vector<int> &current) {
    if ((int)current.size() == k) {
        all_combinations.push_back(current);
        return;
    }
    for (int i = start; i < (int)arr.size(); ++i) {
        current.push_back(arr[i]);
        generate_combinations(arr, k, i + 1, current);
        current.pop_back();
    }
}

// -----------------------------------------------
// N-Queens
// -----------------------------------------------
int n_queens_solutions;

void solve_n_queens(int n, int row, vector<int> &queens,
                    vector<bool> &cols, vector<bool> &d1, vector<bool> &d2) {
    if (row == n) {
        ++n_queens_solutions;
        // Imprimir tablero
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                cout << (queens[i] == j ? "Q " : ". ");
            cout << '\n';
        }
        cout << '\n';
        return;
    }
    for (int col = 0; col < n; ++col) {
        if (!cols[col] && !d1[row - col + n] && !d2[row + col]) {
            queens[row] = col;
            cols[col] = d1[row - col + n] = d2[row + col] = true;
            solve_n_queens(n, row + 1, queens, cols, d1, d2);
            cols[col] = d1[row - col + n] = d2[row + col] = false;
        }
    }
}

int main() {
    // Permutaciones
    vector<int> arr = {1, 2, 3};
    vector<int> cur;
    vector<bool> used(3, false);
    generate_permutations(arr, cur, used);
    cout << "Permutations: " << all_permutations.size() << '\n';

    // Subconjuntos
    cur.clear();
    generate_subsets(arr, 0, cur);
    cout << "Subsets: " << all_subsets.size() << '\n';

    // Combinaciones C(4,2)
    vector<int> arr2 = {1, 2, 3, 4};
    cur.clear();
    generate_combinations(arr2, 2, 0, cur);
    cout << "C(4,2): " << all_combinations.size() << '\n';
    for (auto &c : all_combinations) {
        for (int x : c) cout << x << " ";
        cout << '\n';
    }

    // N-Queens 4x4
    int n = 4;
    vector<int> queens(n);
    vector<bool> cols(n, false), d1(2 * n, false), d2(2 * n, false);
    n_queens_solutions = 0;
    solve_n_queens(n, 0, queens, cols, d1, d2);
    cout << "4-Queens solutions: " << n_queens_solutions << '\n';

    return 0;
}
