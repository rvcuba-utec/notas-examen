#include <bits/stdc++.h>
using namespace std;

template <typename T> struct Queue {
  stack<pair<T, T>> in;
  stack<pair<T, T>> out;

  void push(T x) {
    if (in.empty()) {
      in.push({x, x});
    } else {
      in.push({x, max(in.top().second, x)});
    }
  };

  void pop() {
    if (out.empty()) {
      out.push({in.top().first, in.top().first});
      in.pop();
      while (!in.empty()) {
        out.push({in.top().first, max(in.top().first, out.top().second)});
        in.pop();
      }
      out.pop();
    } else {
      out.pop();
    }
  }

  T maximum() {
    if (!out.empty() && !in.empty()) {
      return max(in.top().second, out.top().second);
    } else if (in.empty()) {
      return out.top().second;
    } else {
      return in.top().second;
    }
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(false); // Fast I/O con cin/cout
  Queue<int> cola;
  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    int op, x;
    cin >> op;
    if (op == 1) {
      cin >> x;
      cola.push(x);
    } else if (op == 2) {
      cola.pop();
    } else if (op == 3) {
      cout << cola.maximum() << '\n';
    }
  }
}
