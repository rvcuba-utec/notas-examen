#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    long long a, b, c;
    cin >> a >> b >> c;
    if (abs(a + c - b) > abs(a - b)) {
      cout << abs(a + c - b) << '\n';
    } else {
      cout << abs(a - b) << '\n';
    }
  }
}
