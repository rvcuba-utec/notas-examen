#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int longestConsecutive(vector<int> &nums) {
    unordered_map<int, int> map;
    int max = 0;
    for (const int &n : nums) {
      map[n] = 1;
    }
    for (const int &n : nums) {
      if (map.find(n - 1) == map.end()) {
        int x = 1;
        while (map.find(n + x) != map.end()) {
          x += 1;
        }
        if (x > max)
          max = x;
      }
    }
    return max;
  }
};
