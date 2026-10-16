#include <iostream>
#include <list>
#include <utility>
using namespace std;

int main() {
  list<pair<int, int>> l1;
  list<pair<int, int>> l2;
  int n, e, c;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> e >> c;
    l1.push_back({e, c});
  }
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> e >> c;
    l2.push_back({e, c});
  }
}
