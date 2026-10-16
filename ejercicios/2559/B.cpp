#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int imp = 0, nomod4 = 0, mod4 = 0;
    while (n--) {
      int a;
      cin >> a;
      if (a % 2 == 1) {
        imp += 1;
      } else {
        if (a % 4 == 0) {
          mod4 += 1;
        } else {
          nomod4 += 1;
        }
      }
    }
    cout << max(imp, max(nomod4, mod4)) << '\n';
  }
}
