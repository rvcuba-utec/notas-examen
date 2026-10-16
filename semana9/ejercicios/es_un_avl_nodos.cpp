#include <bits/stdc++.h>
using namespace std;

struct Node {
  int val;
  int height = 0;
  Node *left = nullptr;
  Node *right = nullptr;
  Node(int v) : val(v) {}
};

int h(Node *u) { return u ? u->height : -1; }

void compute_height(Node *u) {
  if (!u) return;
  compute_height(u->left);
  compute_height(u->right);
  u->height = 1 + max(h(u->left), h(u->right));
}

void get_inorder(Node *u, vector<int> &order) {
  if (!u) return;
  get_inorder(u->left, order);
  order.push_back(u->val);
  get_inorder(u->right, order);
}

bool is_bst(Node *root) {
  vector<int> order;
  get_inorder(root, order);
  for (size_t i = 1; i < order.size(); ++i) {
    if (order[i - 1] >= order[i]) return false;
  }
  return true;
}

bool is_avl(Node *u) {
  if (!u) return true;
  if (abs(h(u->left) - h(u->right)) > 1) return false;
  return is_avl(u->left) && is_avl(u->right);
}

void solve() {
  int n;
  cin >> n;

  vector<Node*> nodes(n + 1, nullptr);
  vector<pair<int, int>> children(n + 1);

  for (int i = 1; i <= n; ++i) {
    int val, l, r;
    cin >> val >> l >> r;
    nodes[i] = new Node(val);
    children[i] = {l, r};
  }

  for (int i = 1; i <= n; ++i) {
    if (children[i].first != 0) nodes[i]->left = nodes[children[i].first];
    if (children[i].second != 0) nodes[i]->right = nodes[children[i].second];
  }

  Node *root = nodes[1];
  compute_height(root);

  if (!is_bst(root)) {
    cout << "NINGUNO\n";
  } else if (!is_avl(root)) {
    cout << "BST\n";
  } else {
    cout << "AVL\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  if (cin >> t) {
    while (t--) solve();
  }
  return 0;
}
