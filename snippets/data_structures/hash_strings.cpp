#include <bits/stdc++.h>
using namespace std;
template <typename value_type> struct hash_strings {
  int m;
  vector<vector<pair<string, value_type>>> chains;
  hash_strings(int m) : m(m) { chains.resize(m); }
  value_type &operator[](const string &key) {
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
  bool has_key(const string &key) const {
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
  int _hash(string key) const {
    // Para enteros
    const int B = 311;
    const int MOD = 1e9 + 7;
    int hash_value = 0;
    for (char c : key) {
      hash_value = (1ll * hash_value * B + c) % MOD;
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
  hash_strings<long long> hash_table(20);
  hash_table["hola"] = 21;
  hash_table["mundo"] = 42;
  hash_table.print();
  return 0;
}
