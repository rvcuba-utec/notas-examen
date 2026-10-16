#include <iostream>
#include <vector>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int n, q;
  cin >> n >> q;
  vector<vector<int>> vec(n);
  for (int i = 0; i < q; i++) {
    int op, t, x;
    cin >> op >> t;
    if (op == 0) {
      cin >> x;
      vec[t].push_back(x);
    } else if (op == 1) {
      if (vec[t].size() > 0) {
        int j = 0;
        for (; j < vec[t].size() - 1; j++) {
          cout << vec[t][j] << " ";
        }

        cout << vec[t][j] << "\n";
      } else {
        cout << "\n";
      }
    } else if (op == 2) {
      vec[t].clear();
    }
  }
}
