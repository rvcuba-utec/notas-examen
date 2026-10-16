#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int x, e, del = 0;
  unordered_map<int, int> conteos;
  cin >> x;
  for (int i = 0; i < x; i++) {
    cin >> e;
    conteos[e]++;
  }
  for (auto &par : conteos) {
    if (par.second >= par.first) {
      del += par.second - par.first;
    } else {
      del += par.second;
    }
  }
  cout << del;
}
