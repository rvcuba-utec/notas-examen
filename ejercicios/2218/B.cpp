#include <bits/stdc++.h>
using namespace std;

long long main() {
  cin.tie(0)->sync_with_stdio(false);
  long long t;
  cin >> t;
  while (t--) {
    long long sumaton = 0;
    long long maxiton = -67;
    long long n;
    for (long long i = 0; i < 7; i++) {
      cin >> n;
      sumaton += n;
      if (n > maxiton) {
        maxiton = n;
      }
    }
    sumaton -= maxiton;
    cout << maxiton - sumaton << '\n';
  }
}
