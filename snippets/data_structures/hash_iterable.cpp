#include <bits/stdc++.h>
using namespace std;

template <typename key_type, typename value_type> struct hash_iterable {
  int m;
  vector<vector<pair<key_type, value_type>>> chains;
  
  hash_iterable(int m) : m(m) { chains.resize(m); }
  
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

  struct iterator {
    vector<vector<pair<key_type, value_type>>>* chains_ptr;
    int bucket_idx;
    int element_idx;

    iterator(vector<vector<pair<key_type, value_type>>>* c, int b, int e) 
        : chains_ptr(c), bucket_idx(b), element_idx(e) {
      advance_to_valid();
    }

    void advance_to_valid() {
      while (bucket_idx < chains_ptr->size() && 
             element_idx >= (*chains_ptr)[bucket_idx].size()) {
        bucket_idx++;
        element_idx = 0;
      }
    }

    iterator& operator++() {
      element_idx++;
      advance_to_valid();
      return *this;
    }

    bool operator!=(const iterator& other) const {
      return bucket_idx != other.bucket_idx || element_idx != other.element_idx;
    }

    pair<key_type, value_type>& operator*() {
      return (*chains_ptr)[bucket_idx][element_idx];
    }
  };

  iterator begin() {
    return iterator(&chains, 0, 0);
  }

  iterator end() {
    return iterator(&chains, m, 0);
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
  hash_iterable<int, string> hash_table(20);
  
  hash_table[15] = "Quince";
  hash_table[32] = "Treinta y dos";
  hash_table[99] = "Noventa y nueve";
  hash_table[7]  = "Siete";
  
  for (auto const& p : hash_table) {
    cout << p.first << " = " << p.second << endl;
  }
  
  return 0;
}
