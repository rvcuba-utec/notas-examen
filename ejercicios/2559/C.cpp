#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> ar(n);
    for (int i = 0; i < n; i++) {
      cin >> ar[i];
    }
    bool izq1 = false;
    bool der1 = false;
    for (int i = 0; i < n; i++) {
      if (ar[i] == 1)
        break;
      else if (ar[i] == -1) {
        ar[i] = 1;
        break;
      }
    }
    for (int i = n - 1; i >= 0; i--) {
      if (ar[i] == 1)
        break;
      else if (ar[i] == -1) {
        ar[i] = 1;
        break;
      }
    }
    for (int i = 0; i < n; i++) {
      if (ar[i] == -1)
        ar[i] = 0;
      cout << ar[i] << " \n"[i + 1 == n];
    }
  }
}
