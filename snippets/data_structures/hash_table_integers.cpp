#include <bits/stdc++.h>
using namespace std;

template <typename key_type, typename value_type> struct my_map_int {
  int m;
  int _size;
  vector<vector<pair<key_type, value_type>>> chains;

  my_map_int(int m = 1000) : m(m), _size(0) { chains.resize(m); }

  value_type &operator[](const key_type &key) {
    int chain_position = _hash(key);
    int at = 0;
    while (at < chains[chain_position].size() and
           chains[chain_position][at].first != key) {
      ++at;
    }
    if (at == chains[chain_position].size()) {
      chains[chain_position].emplace_back(key, value_type());
      ++_size;
    }
    return chains[chain_position][at].second;
  }

  void erase(const key_type &key) {
    int chain_position = _hash(key);
    int at = 0;
    while (at < chains[chain_position].size() and
           chains[chain_position][at].first != key) {
      ++at;
    }
    if (at != chains[chain_position].size()) {
      if (at + 1 < chains[chain_position].size()) {
        swap(chains[chain_position][at], chains[chain_position].back());
      }
      chains[chain_position].pop_back();
      --_size;
    }
  }

  bool has_key(const key_type &key) const {
    int chain_position = _hash(key);
    int at = 0;
    while (at < chains[chain_position].size() and
           chains[chain_position][at].first != key) {
      ++at;
    }
    return at != chains[chain_position].size();
  }

  int _hash(key_type key) const {
    const int B = 311;
    const int MOD = 1e9 + 7;
    int hash_value = 0;
    
    if (key == 0) return 0;
    
    bool is_negative = false;
    long long k = key; 
    if (k < 0) {
        is_negative = true;
        k = -k;
    }
    
    while (k > 0) {
      int d = k % 10;
      hash_value = (1ll * hash_value * B + (d + 1)) % MOD;
      k /= 10;
    }
    
    if (is_negative) {
        hash_value = (1ll * hash_value * B + 2) % MOD;
    }
    
    return hash_value % m;
  }

  int size() const { return _size; }

  bool empty() const { return _size == 0; }

  void print() {
    for (int i = 0; i < m; ++i) {
      if(chains[i].empty()) continue;
      cout << "Bucket " << i << ": " << endl;
      for (auto &e : chains[i]) {
        cout << e.first << " --> " << e.second << endl;
      }
      cout << "End bucket" << endl;
    }
  }
};
