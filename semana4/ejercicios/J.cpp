#include <bits/stdc++.h>
using namespace std;

struct maxicola {
  queue<int> nums;
  deque<int> maxis;

  void push(int x) {
    nums.push(x);
    while (!maxis.empty() && maxis.back() < x) {
      maxis.pop_back();
    }
    maxis.push_back(x);
  }

  void pop() {
    if (maxis.front() == nums.front())
      maxis.pop_front();
    nums.pop();
  }

  int maximum() { return maxis.front(); }
};

int foo(vector<int> &nums, int &d) {
  int min = 1000000;
  maxicola cola;
  for (int i = 0; i < d - 1; i++) {
    cola.push(nums[i]);
  }
  for (int i = d - 1; i < nums.size(); i++) {
    cola.push(nums[i]);
    if (cola.maximum() < min)
      min = cola.maximum();
    cola.pop();
  }
  return min;
}

int main() {
  cin.tie(0)->sync_with_stdio(false); // Fast I/O con cin/cout
  int n, q;
  cin >> n >> q;
  int num;
  vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    cin >> num;
    nums[i] = num;
  }
  for (int i = 0; i < q; ++i) {
    int d;
    cin >> d;
    cout << foo(nums, d) << '\n';
  }
}
