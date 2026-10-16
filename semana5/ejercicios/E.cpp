#include <bits/stdc++.h>
using namespace std;

template <typename key_type, typename value_type> struct my_map {
  int m;
  vector<vector<pair<key_type, value_type>>> chains;
  my_map(int m) : m(m) { chains.resize(m); }
  value_type &operator[](const key_type &key) {
    int chain_position = _hash(key);
    int at = 0;
    while (at < chains[chain_position].size() and
           chains[chain_position][at].first != key) {
      ++at;
    }
    if (at == chains[chain_position].size()) {
      chains[chain_position].emplace_back(key, value_type());
    }
    return chains[chain_position][at].second;
  }
  bool has_key(const key_type &key) const {
    int chain_position = _hash(key);
    int at = 0;
    while (at < chains[chain_position].size() and
           chains[chain_position][at].first != key) {
      ++at;
    }
    if (at == chains[chain_position].size()) {
      return false;
    }
    return true;
  }

  int size() const {
    int result = 0;
    for (int i = 0; i < m; ++i)
      result += chains[i].size();
    return result;
  }

  int _hash(key_type key) const {
    // Para enteros
    const int B = 311;
    const int MOD = 1e9 + 7;
    int hash_value = 0;
    while (key > 0) {
      int d = key % 10;
      hash_value = (1ll * hash_value * B + (d + 1)) % MOD;
      key /= 10;
    }
    return hash_value % m;
  }
  void print() {
    for (int i = 0; i < m; ++i) {
      cout << "Bucket " << i << ": " << endl;
      for (auto &e : chains[i]) {
        cout << e.first << " --> " << e.second << endl;
      }
      cout << "End bucket" << endl;
    }
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(false); // Fast I/O con cin/cout
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  my_map<int, int> frecuencias(2 * n);
  stack<int> candidates;
  for (int i = n - 1; i >= 0; --i) {
    ++frecuencias[a[i]];
    if (frecuencias[a[i]] == 1) {
      candidates.push(a[i]);
    }
    while (not candidates.empty() and frecuencias[candidates.top()] > 1) {
      candidates.pop();
    }
  }
  cout << (candidates.empty() ? -1 : candidates.top());
}
