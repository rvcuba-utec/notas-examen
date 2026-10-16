#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3,
                   vector<int> &nums4) {
    unordered_map<int, int> map;
    for (const int &n1 : nums1) {
      for (const int &n2 : nums2) {
        map[n1 + n2]++;
      }
    }
    int cant = 0;
    for (const int &n3 : nums3) {
      for (const int &n4 : nums4) {
        if (map.find(-(n3 + n4)) != map.end()) {
          cant += map[-(n3 + n4)];
        }
      }
    }
    return cant;
  }
};
