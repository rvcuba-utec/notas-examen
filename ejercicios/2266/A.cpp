#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int maxi = 0;
    for (int i = 0; i < 3; i++) {
      int a;
      cin >> a;
      if (n - a > maxi)
        maxi = n - a;
    }
    cout << maxi << '\n';
  }
}
