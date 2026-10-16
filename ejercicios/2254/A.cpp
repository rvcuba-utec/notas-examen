#include <bits/stdc++.h>
using namespace std;

long long main() {
  cin.tie(0)->sync_with_stdio(false);
  long long t;
  cin >> t;
  while (t--) {
    long long a, b, c;
    cin >> a >> b >> c;
    if (a == b || b == c) {
      cout << 0 << '\n';
    } else {
      long long maxiton = max(a, max(b, c));
      long long mlong longon = min(min(a, b), c);
      long long mediton = a + b + c - maxiton - mlong longon;
      cout << min(maxiton - mediton, mediton - mlong longon) << '\n';
    }
  }
}
