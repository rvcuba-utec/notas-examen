#include <bits/stdc++.h>
using namespace std;

template <typename value_type> struct hash_pairs {
  int m;
  vector<vector<pair<pair<int, int>, value_type>>> chains;
  
  hash_pairs(int m) : m(m) { chains.resize(m); }
  
  value_type &operator[](const pair<int, int> &key) {
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
  
  bool has_key(const pair<int, int> &key) const {
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
  
  int _hash(const pair<int, int> &key) const {
    // Para enteros
    const int B1 = 311;
    const int B2 = 313;
    const int MOD = 1e9 + 7;
    
    long long h1 = (key.first % MOD + MOD) % MOD;
    long long h2 = (key.second % MOD + MOD) % MOD;
    
    long long hash_value = (h1 * B1 + h2 * B2) % MOD;
    return hash_value % m;
  }
  
  void print() {
    for (int i = 0; i < m; ++i) {
      cout << "Bucket " << i << ": " << endl;
      for (auto &e : chains[i]) {
        cout << "(" << e.first.first << ", " << e.first.second << ") --> " << e.second << endl;
      }
      cout << "End bucket" << endl;
    }
  }
};

int main() {
  hash_pairs<int> hash_table(20);
  hash_table[{1, 2}] = 100;
  hash_table[{3, 4}] = 200;
  hash_table.print();
  return 0;
}
