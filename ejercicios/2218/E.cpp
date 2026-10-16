#include <bits/stdc++.h>
using namespace std;

long long main() {
  cin.tie(0)->sync_with_stdio(false);
  long long t;
  cin >> t;
  while (t--) {
    long long n;
    cin >> n;
    vector<long long> a(n);
    for (long long i = 0; i < n; i++) {
      cin >> a[i];
    }
    long long max = 0;
    for (long long i = 0; i < n; i++) {
      for (long long j = i + 1; j < n; j++) {
        long long op = a[i] ^ a[j] ^ 0;
        if (op > max)
          max = op;
      }
    }
    cout << max << '\n';
  }
}
