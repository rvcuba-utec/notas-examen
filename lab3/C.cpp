// https://github.com/josevillalobostc/aed/blob/main/snippets/data_structures/hash_clase2.cpp
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
  int _hash(key_type key) const {
    const int B = 311;
    const int MOD = 1e9 + 7;
    int hash_value = 0;
    if (key == 0)
      return 0;
    long long k = key;
    bool is_neg = false;
    if (k < 0) {
      is_neg = true;
      k = -k;
    }
    while (k > 0) {
      int d = k % 10;
      hash_value = (1ll * hash_value * B + (d + 1)) % MOD;
      k /= 10;
    }
    if (is_neg) {
      hash_value = (1ll * hash_value * B + 2) % MOD;
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
  vector<int> v1(n);
  vector<int> v2(n);
  vector<int> v3(n);
  vector<int> v4(n);

  for (int i = 0; i < n; i++) {
    cin >> v1[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> v2[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> v3[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> v4[i];
  }
  my_map<int, int> map(n * n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      map[v1[i] + v2[j]] += 1;
    }
  }
  long long cant = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int suma = v3[i] + v4[j];
      if (map.has_key(-suma)) {
        cant += map[-suma];
      }
    }
  }
  cout << cant;
}
