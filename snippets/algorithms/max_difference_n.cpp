// ============================================================
// Máxima diferencia a[j] - a[i] donde j > i (Best Time to
// Buy and Sell Stock) + variantes
// ============================================================
// Complejidad: O(n) tiempo, O(1) espacio
//
// Uso: Encontrar la máxima ganancia comprando y vendiendo,
//      donde la venta debe ser posterior a la compra.
//
// Aplicaciones:
//   - Best Time to Buy and Sell Stock (1 transacción)
//   - Máxima diferencia positiva en un arreglo
//   - Variante: múltiples transacciones
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------
// Máxima diferencia a[j] - a[i] con j > i
// -----------------------------------------------
// Idea: mantener el mínimo visto hasta ahora
pair<int, pair<int,int>> max_difference(vector<int> &arr) {
    int min_so_far = arr[0];
    int min_idx = 0;
    int max_diff = INT_MIN;
    int buy = 0, sell = 0;

    for (int i = 1; i < (int)arr.size(); ++i) {
        if (arr[i] - min_so_far > max_diff) {
            max_diff = arr[i] - min_so_far;
            buy = min_idx;
            sell = i;
        }
        if (arr[i] < min_so_far) {
            min_so_far = arr[i];
            min_idx = i;
        }
    }

    return {max_diff, {buy, sell}};
}

// -----------------------------------------------
// Best Time to Buy and Sell Stock II
// (múltiples transacciones permitidas)
// -----------------------------------------------
// Idea: sumar todas las subidas consecutivas
int max_profit_multiple(vector<int> &arr) {
    int profit = 0;
    for (int i = 1; i < (int)arr.size(); ++i) {
        if (arr[i] > arr[i - 1]) {
            profit += arr[i] - arr[i - 1];
        }
    }
    return profit;
}

int main() {
    vector<int> prices = {7, 1, 5, 3, 6, 4};

    auto [diff, indices] = max_difference(prices);
    auto [buy, sell] = indices;
    cout << "Buy at index " << buy << " (price " << prices[buy]
         << "), sell at index " << sell << " (price " << prices[sell]
         << "), profit = " << diff << '\n';

    cout << "Max profit (multiple): " << max_profit_multiple(prices) << '\n'; // 7

    return 0;
}
