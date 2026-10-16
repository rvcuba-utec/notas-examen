#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    string cad;
    cin >> cad;
    int cant = 0;
    for (int i = 0; i < n; i += k) {
      bool tiene = true;
      for (int j = i; j < i + k; j++) {
        if (cad[j] == '0') {
          tiene = false;
          continue;
        }
      }
      if (tiene)
        cant += 1;
    }
    cout << cant << '\n';
  }
}
