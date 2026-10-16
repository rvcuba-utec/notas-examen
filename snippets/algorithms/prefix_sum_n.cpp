// ============================================================
// Prefix Sum - Suma de prefijos (1D y 2D)
// ============================================================
// Complejidad: O(n) construcción, O(1) por consulta (1D)
//              O(n*m) construcción, O(1) por consulta (2D)
//
// Uso: Responder consultas de suma en rangos [l, r] en O(1)
//      después de un preprocesamiento O(n).
//
// Aplicaciones:
//   - Suma de rango en arreglo estático
//   - Difference array (actualizaciones en rango)
//   - Suma de submatrices (2D)
//   - Contar elementos en rangos
//   - Técnica de "prefix XOR" para XOR en rangos
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------
// PREFIX SUM 1D
// -----------------------------------------------
struct PrefixSum1D {
    vector<long long> prefix;

    PrefixSum1D(vector<int> &arr) {
        int n = arr.size();
        prefix.resize(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + arr[i];
        }
    }

    // Suma del rango [l, r] (0-indexed, inclusive)
    long long range_sum(int l, int r) {
        return prefix[r + 1] - prefix[l];
    }
};

// -----------------------------------------------
// DIFFERENCE ARRAY 1D
// -----------------------------------------------
// Permite hacer actualizaciones en rango [l, r] += val en O(1)
// y luego reconstruir el arreglo en O(n)
struct DifferenceArray {
    vector<long long> diff;
    int n;

    DifferenceArray(int n) : n(n), diff(n + 1, 0) {}

    void range_update(int l, int r, long long val) {
        diff[l] += val;
        diff[r + 1] -= val;
    }

    vector<long long> build() {
        vector<long long> result(n);
        result[0] = diff[0];
        for (int i = 1; i < n; ++i) {
            result[i] = result[i - 1] + diff[i];
        }
        return result;
    }
};

// -----------------------------------------------
// PREFIX SUM 2D
// -----------------------------------------------
struct PrefixSum2D {
    vector<vector<long long>> prefix;

    PrefixSum2D(vector<vector<int>> &matrix) {
        int rows = matrix.size(), cols = matrix[0].size();
        prefix.assign(rows + 1, vector<long long>(cols + 1, 0));

        for (int i = 1; i <= rows; ++i) {
            for (int j = 1; j <= cols; ++j) {
                prefix[i][j] = matrix[i - 1][j - 1]
                             + prefix[i - 1][j]
                             + prefix[i][j - 1]
                             - prefix[i - 1][j - 1];
            }
        }
    }

    // Suma de submatriz [(r1,c1), (r2,c2)] (0-indexed, inclusive)
    long long range_sum(int r1, int c1, int r2, int c2) {
        return prefix[r2 + 1][c2 + 1]
             - prefix[r1][c2 + 1]
             - prefix[r2 + 1][c1]
             + prefix[r1][c1];
    }
};

int main() {
    // Ejemplo 1D
    vector<int> arr = {1, 3, 5, 2, 8, 4};
    PrefixSum1D ps(arr);
    cout << "Sum [1, 3] = " << ps.range_sum(1, 3) << '\n'; // 3+5+2 = 10

    // Ejemplo Difference Array
    DifferenceArray da(5);
    da.range_update(1, 3, 3);
    da.range_update(2, 4, 2);
    auto result = da.build();
    cout << "After updates: ";
    for (auto x : result) cout << x << " ";
    cout << '\n'; // 0 3 5 5 2

    // Ejemplo 2D
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    PrefixSum2D ps2d(matrix);
    cout << "Submatrix [(0,0),(1,1)] = " << ps2d.range_sum(0, 0, 1, 1) << '\n'; // 1+2+4+5=12

    return 0;
}
