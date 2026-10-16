#include <bits/stdc++.h>
using namespace std;

const long long N = 2000000 + 5;

long long n;
long long a[N];
long long L[N];
long long R[N];

void compute_heights() {}

long long main() {
  cin.tie(0)->sync_with_stdio(false);
  long long t;
  cin >> t;
  while (t--) {
    cin >> n;
    for (long long i = 1; i <= n; ++i) {
      cin >> a[i] >> L[i] >> R[i];
    }
  }
  return 0;
}
