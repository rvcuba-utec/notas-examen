#include <bits/stdc++.h>
using namespace std;

template <typename value_type> struct hash_vector {
  int m;
  vector<vector<pair<vector<int>, value_type>>> chains;
  
  hash_vector(int m) : m(m) { chains.resize(m); }
  
  value_type &operator[](const vector<int> &key) {
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
  
  bool has_key(const vector<int> &key) const {
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
  
  int _hash(const vector<int> &key) const {
    // Para enteros
    const int B = 311;
    const int MOD = 1e9 + 7;
    int hash_value = 0;
    for (int x : key) {
      long long val = (x % MOD + MOD) % MOD;
      hash_value = (1ll * hash_value * B + val) % MOD;
    }
    return hash_value % m;
  }
  
  void print() {
    for (int i = 0; i < m; ++i) {
      cout << "Bucket " << i << ": " << endl;
      for (auto &e : chains[i]) {
        cout << "[ ";
        for(int x : e.first) cout << x << " ";
        cout << "] --> " << e.second << endl;
      }
      cout << "End bucket" << endl;
    }
  }
};

int main() {
  hash_vector<int> hash_table(20);
  hash_table[{1, 2, 3}] = 100;
  hash_table[{4, 5}] = 200;
  hash_table.print();
  return 0;
}
