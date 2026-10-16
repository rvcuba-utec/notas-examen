#include <bits/stdc++.h>
using namespace std;

void foo(string &S, int ab, int ce, int n) {
  if (ab + ce == 2 * n) {
    cout << S << "\n";
    return;
  }
  if (ab < n) {
    S += "(";
    foo(S, ab + 1, ce, n);
    S.pop_back();
  }
  if (ce < n && ab - ce > 0) {
    S += ")";
    foo(S, ab, ce + 1, n);
    S.pop_back();
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int n;
  cin >> n;
  string S = "";
  foo(S, 0, 0, n);
}
