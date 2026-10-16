// ============================================================
// Monotonic Stack - Next Greater / Smaller Element
// ============================================================
// Complejidad: O(n) tiempo, O(n) espacio
//
// Uso: Para cada elemento del arreglo, encontrar el siguiente
//      (o anterior) elemento mayor (o menor).
//
// Aplicaciones:
//   - Next Greater Element (NGE)
//   - Previous Greater Element (PGE)
//   - Next Smaller Element (NSE)
//   - Previous Smaller Element (PSE)
//   - Largest Rectangle in Histogram
//   - Stock Span Problem
//   - Trapping Rain Water
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------
// Next Greater Element (NGE)
// -----------------------------------------------
// nge[i] = índice del siguiente elemento > arr[i], o -1
vector<int> next_greater_element(vector<int> &arr) {
    int n = arr.size();
    vector<int> nge(n, -1);
    stack<int> st;

    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && arr[st.top()] <= arr[i]) st.pop();
        nge[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return nge;
}

// -----------------------------------------------
// Next Smaller Element (NSE)
// -----------------------------------------------
vector<int> next_smaller_element(vector<int> &arr) {
    int n = arr.size();
    vector<int> nse(n, -1);
    stack<int> st;

    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && arr[st.top()] >= arr[i]) st.pop();
        nse[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return nse;
}

// -----------------------------------------------
// Previous Greater Element (PGE)
// -----------------------------------------------
vector<int> prev_greater_element(vector<int> &arr) {
    int n = arr.size();
    vector<int> pge(n, -1);
    stack<int> st;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && arr[st.top()] <= arr[i]) st.pop();
        pge[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return pge;
}

// -----------------------------------------------
// Previous Smaller Element (PSE)
// -----------------------------------------------
vector<int> prev_smaller_element(vector<int> &arr) {
    int n = arr.size();
    vector<int> pse(n, -1);
    stack<int> st;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && arr[st.top()] >= arr[i]) st.pop();
        pse[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return pse;
}

// -----------------------------------------------
// Largest Rectangle in Histogram
// -----------------------------------------------
long long largest_rectangle(vector<int> &heights) {
    int n = heights.size();
    auto pse = prev_smaller_element(heights);
    auto nse = next_smaller_element(heights);

    long long max_area = 0;
    for (int i = 0; i < n; ++i) {
        int left = pse[i] + 1;
        int right = (nse[i] == -1) ? n - 1 : nse[i] - 1;
        long long area = (long long)heights[i] * (right - left + 1);
        max_area = max(max_area, area);
    }
    return max_area;
}

// -----------------------------------------------
// Trapping Rain Water
// -----------------------------------------------
int trap_rain_water(vector<int> &height) {
    int n = height.size();
    if (n < 3) return 0;

    vector<int> left_max(n), right_max(n);
    left_max[0] = height[0];
    for (int i = 1; i < n; ++i) left_max[i] = max(left_max[i - 1], height[i]);
    right_max[n - 1] = height[n - 1];
    for (int i = n - 2; i >= 0; --i) right_max[i] = max(right_max[i + 1], height[i]);

    int water = 0;
    for (int i = 0; i < n; ++i) {
        water += min(left_max[i], right_max[i]) - height[i];
    }
    return water;
}

int main() {
    vector<int> arr = {4, 5, 2, 10, 8};
    auto nge = next_greater_element(arr);

    cout << "Next Greater Element:\n";
    for (int i = 0; i < (int)arr.size(); ++i) {
        cout << arr[i] << " -> " << (nge[i] == -1 ? -1 : arr[nge[i]]) << '\n';
    }

    vector<int> hist = {2, 1, 5, 6, 2, 3};
    cout << "\nLargest rectangle: " << largest_rectangle(hist) << '\n'; // 10

    vector<int> rain = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "Trapped water: " << trap_rain_water(rain) << '\n'; // 6

    return 0;
}
