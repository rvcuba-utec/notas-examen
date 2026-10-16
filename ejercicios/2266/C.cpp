#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int unos = 0;
    int cant = 0;
    for (int i = 0; i < n; i++) {
      if (s[i] == '1') {
        unos++;
      }
    }
    int ceros = n - unos;
    unos = 0;
    int min = n;
    if (s[0] == '1') {
      for (int i = 1; i < n; i++) {
        if (s[i] == '0')
          cant++;
      }
    } else {
      for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
          ceros--;
          int cambios = ceros + unos;
          if (cambios < min)
            min = cambios;
        } else {
          int cambios = ceros + unos;
          if (cambios < min)
            min = cambios;
          unos++;
        }
      }
      cant = min;
    }
    cout << cant << '\n';
  }
}
