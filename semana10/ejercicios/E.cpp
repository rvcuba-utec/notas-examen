#include <bits/stdc++.h>
using namespace std;

void foo(vector<vector<int>> &tab, int &cont, int fil, int n) {
  for (int i = 0; i < n; i++) {
    if (tab[fil][i] == 0) {
      for (int j = 0; j < fil; j++) {
        if (tab[j][i] != 2) {
          continue;
        };
      }
    }
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int n;
  cin >> n;
  string s;
  vector<vector<int>> tab;
  for (int i = 0; i < n; i++) {
    cin >> s;
    for (int j = 0; i < n; i++) {
      if (s[j] == '.') {
        tab[i][j] = 0;
      } else {
        tab[i][j] = 1;
      }
    }
  }
  int cont = 0;
  foo(tab, cont, 0, n);
}
