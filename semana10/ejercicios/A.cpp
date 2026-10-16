#include <bits/stdc++.h>
using namespace std;

struct binario {
  long long n;
  binario(long long tam) : n(tam) {
    vector<long long> nuevovec(tam, 0);
    valor = nuevovec;
  }
  vector<long long> valor;

  void sumaruno() {
    long long carry = 1;
    long long i = 0;
    while (carry && i < n) {
      if (valor[i] == 0) {
        valor[i] = 1;
        carry = 0;
      } else {
        valor[i] = 0;
        i++;
      }
    }
  }

  bool escero() {
    bool rpta = true;
    for (long long i = 0; i < n; i++) {
      rpta = rpta && (valor[i] == 0);
    }
    return rpta;
  }
};

long long main() {
  cin.tie(0)->sync_with_stdio(false);
  long long n, s;
  cin >> n >> s;
  vector<long long> nums(n);
  binario elbin(n);
  for (long long i = 0; i < n; i++) {
    cin >> nums[i];
  }
  long long cant = 0;
  do {
    long long suma = 0;
    for (long long i = 0; i < n; i++) {
      suma += elbin.valor[i] * nums[i];
    }
    if (suma == s) {
      cant += 1;
    }
    elbin.sumaruno();
  } while (!elbin.escero());
  cout << cant;
}
