#include <bits/stdc++.h>
using namespace std;

struct Node {
  int id;
  Node *left = nullptr;
  Node *right = nullptr;
  Node *parent = nullptr;
  Node(int id) : id(id) {}
};

Node *root = nullptr;

void rotate_left(Node *x) {
  Node *y = x->right;
  Node *p = x->parent;

  x->right = y->left;
  if (y->left) y->left->parent = x;

  y->parent = p;
  if (p) {
    if (p->left == x) p->left = y;
    else p->right = y;
  } else {
    root = y;
  }

  y->left = x;
  x->parent = y;
}

void rotate_right(Node *y) {
  Node *x = y->left;
  Node *p = y->parent;

  y->left = x->right;
  if (x->right) x->right->parent = y;

  x->parent = p;
  if (p) {
    if (p->left == y) p->left = x;
    else p->right = x;
  } else {
    root = x;
  }

  x->right = y;
  y->parent = x;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  if (!(cin >> n >> q)) return 0;

  vector<Node*> nodes(n + 1, nullptr);
  for (int i = 1; i <= n; ++i) {
    nodes[i] = new Node(i);
  }

  for (int i = 1; i <= n; ++i) {
    int l, r;
    cin >> l >> r;
    if (l != 0) {
      nodes[i]->left = nodes[l];
      nodes[l]->parent = nodes[i];
    }
    if (r != 0) {
      nodes[i]->right = nodes[r];
      nodes[r]->parent = nodes[i];
    }
  }

  root = nodes[1];

  while (q--) {
    char op;
    int x;
    cin >> op >> x;
    if (op == 'I') rotate_left(nodes[x]);
    else rotate_right(nodes[x]);
  }

  cout << root->id << '\n';
  for (int i = 1; i <= n; ++i) {
    int l = nodes[i]->left ? nodes[i]->left->id : 0;
    int r = nodes[i]->right ? nodes[i]->right->id : 0;
    cout << l << " " << r << '\n';
  }

  return 0;
}
