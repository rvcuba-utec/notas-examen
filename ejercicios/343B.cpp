#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(false); // Fast I/O con cin/cout

  stack<char> s;

  string cad;
  cin >> cad;
  for (char c : cad) {
    if (!s.empty() && s.top() == c) {
      s.pop();
    } else {
      s.push(c);
    }
  }
  cout << (s.empty() ? "Yes" : "No");
  return 0;
}
