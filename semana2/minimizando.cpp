#include <iostream>
#include <vector>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int n, t;
  cin >> n;
  vector<int> vec(n);
  for (int i = 0; i < n; i++) {
    cin >> t;
    vec.push_back(t);
  }
  int cont = 0;
  int valido;
  do {
    for (int &num : vec) {
      if (num % 2 == 0) {
        num = num / 2;
        valido = true;
      } else {
        valido = false;
        break;
      }
    }
    if (valido) {
      cont += 1;
    }
  } while (valido);
  cout << cont;
}
