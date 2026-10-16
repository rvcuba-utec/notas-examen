#include <iostream>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  string cad;
  string hello = "hello";
  int j = 0;
  cin >> cad;
  for (int i = 0; i < cad.size() && j < 5; i++) {
    if (cad[i] == hello[j]) {
      j++;
    }
  }
  if (j < 5) {
    cout << "NO";
  } else {
    cout << "YES";
  }
}
