#include <bits/stdc++.h>
using namespace std;

template <typename key_type, typename value_type> struct my_map_gen {
  int m;
  int _size;
  vector<vector<pair<key_type, value_type>>> chains;

  my_map_gen(int m = 1000) : m(m), _size(0) { chains.resize(m); }

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

  int _hash(const key_type &key) const {
    return std::hash<key_type>{}(key) % m;
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
