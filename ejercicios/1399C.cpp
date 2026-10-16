#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false); // Fast I/O con cin/cout
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
      cin >> nums[i];
    }
    int maxim = 0;
    for (int i = 2; i <= 2 * n; i++) {
      int cant = 0;
      vector<int> conteos(n + 1, 0);
      for (int j = 0; j < n; j++) {
        int peso = nums[j];
        int comp = i - peso;

        if (comp > 0 && comp <= n && conteos[comp] > 0) {
          cant += 1;
          conteos[comp]--;
        } else {
          conteos[peso] += 1;
        }
      }
      maxim = max(cant, maxim);
    }
    cout << maxim << '\n';
  }
  return 0;
}
