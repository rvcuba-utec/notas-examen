#include <bits/stdc++.h>
using namespace std;

long long main() {
  cin.tie(0)->sync_with_stdio(false);
  long long t;
  cin >> t;
  while (t--) {
    long long n;
    cin >> n;
    vector<long long> a(3 * n, 0);
    long long minitin = 1;
    long long maxitin = 3 * n;
    for (long long i = 0; i < 3 * n; i++) {
      if (i % 3 == 0) {
        a[i] = minitin;
        minitin++;
      } else if (i % 3 == 1) {
        a[i] = maxitin - 1;
      } else {
        a[i] = maxitin;
        maxitin -= 2;
      }
    }
    for (const long long &num : a) {
      cout << num << " ";
    }
    cout << '\n';
  }
}
