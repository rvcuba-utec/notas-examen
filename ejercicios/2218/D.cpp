#include <bits/stdc++.h>
using namespace std;

long long main() {
  cin.tie(0)->sync_with_stdio(false);
  long long t;
  cin >> t;
  while (t--) {
    long long n;
    cin >> n;
    for (long long i = 0; i < n; i++) {
      cout << (2 * i + 1) * (2 * i + 3) << ' ';
    }
    cout << '\n';
  }
}
