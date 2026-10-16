#include <bits/stdc++.h>

using namespace std;

struct AVL {
  struct TreeNode {
    int height;
    pair<int, int> data; // {s, e}
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;

    TreeNode(pair<int, int> data = {0, 0}, int height = 0,
             TreeNode *left = nullptr, TreeNode *right = nullptr,
             TreeNode *parent = nullptr)
        : height(height), data(data), left(left), right(right), parent(parent) {
    }
  };

  TreeNode *root;

  AVL() : root(nullptr) {}

  int h(TreeNode *v) { return (v == nullptr ? -1 : v->height); }

  void update(TreeNode *v) { v->height = 1 + max(h(v->left), h(v->right)); }

  int FB(TreeNode *v) { return h(v->left) - h(v->right); }

  TreeNode *rotate_right(TreeNode *y) {
    TreeNode *x = y->left;
    y->left = x->right;
    if (x->right != nullptr)
      x->right->parent = y;
    x->parent = y->parent;
    x->right = y;
    y->parent = x;
    update(y);
    update(x);
    return x;
  }

  TreeNode *rotate_left(TreeNode *x) {
    TreeNode *y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
      y->left->parent = x;
    y->parent = x->parent;
    y->left = x;
    x->parent = y;
    update(x);
    update(y);
    return y;
  }

  TreeNode *rebalance(TreeNode *v) {
    update(v);
    if (FB(v) > 1) {
      if (FB(v->left) < 0) {
        v->left = rotate_left(v->left);
      }
      return rotate_right(v);
    }
    if (FB(v) < -1) {
      if (FB(v->right) > 0) {
        v->right = rotate_right(v->right);
      }
      return rotate_left(v);
    }
    return v;
  }

  void insert(pair<int, int> value) {
    root = insert(root, value);
    if (root != nullptr)
      root->parent = nullptr;
  }

  TreeNode *insert(TreeNode *u, pair<int, int> value) {
    if (u == nullptr) {
      return new TreeNode(value, 0);
    }
    if (value.first < u->data.first) {
      u->left = insert(u->left, value);
      u->left->parent = u;
    } else {
      u->right = insert(u->right, value);
      u->right->parent = u;
    }
    return rebalance(u);
  }

  TreeNode *search(int s) {
    TreeNode *current = root;
    while (current != nullptr) {
      if (current->data.first == s)
        return current;
      if (s < current->data.first)
        current = current->left;
      else
        current = current->right;
    }
    return nullptr;
  }

  // Reserva con el menor inicio >= s
  TreeNode *successor(int s) {
    TreeNode *current = root;
    TreeNode *ans = nullptr;
    while (current != nullptr) {
      if (current->data.first >= s) {
        ans = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return ans;
  }

  // Reserva con el mayor inicio <= s
  TreeNode *predecessor(int s) {
    TreeNode *current = root;
    TreeNode *ans = nullptr;
    while (current != nullptr) {
      if (current->data.first <= s) {
        ans = current;
        current = current->right;
      } else {
        current = current->left;
      }
    }
    return ans;
  }

  TreeNode *min_element(TreeNode *u) {
    if (u == nullptr)
      return nullptr;
    while (u->left != nullptr)
      u = u->left;
    return u;
  }

  TreeNode *tree_successor(TreeNode *x) {
    if (x->right != nullptr)
      return min_element(x->right);
    TreeNode *y = x->parent;
    while (y != nullptr && y->right == x) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  void transplant(TreeNode *u, TreeNode *v) {
    if (u->parent == nullptr) {
      root = v;
    } else if (u->parent->right == u) {
      u->parent->right = v;
    } else {
      u->parent->left = v;
    }
    if (v != nullptr) {
      v->parent = u->parent;
    }
    delete u;
  }

  void erase(TreeNode *u) {
    if (u == nullptr)
      return;
    TreeNode *p = u->parent;
    if (u->left == nullptr && u->right == nullptr) {
      transplant(u, u->left);
    } else if (u->left != nullptr && u->right != nullptr) {
      TreeNode *succ = tree_successor(u);
      u->data = succ->data;
      p = succ->parent;
      transplant(succ, succ->right);
    } else {
      if (u->left)
        transplant(u, u->left);
      else
        transplant(u, u->right);
    }
    while (p != nullptr) {
      TreeNode *parent = p->parent;
      if (parent == nullptr) {
        root = rebalance(p);
        root->parent = nullptr;
      } else if (parent->left == p) {
        parent->left = rebalance(p);
        parent->left->parent = parent;
      } else {
        parent->right = rebalance(p);
        parent->right->parent = parent;
      }
      p = parent;
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  AVL tree;
  int q;
  if (!(cin >> q))
    return 0;

  while (q--) {
    int op;
    cin >> op;

    if (op == 1) {
      int s, e;
      cin >> s >> e;

      auto succ = tree.successor(s);
      auto pred = tree.predecessor(s);

      bool chocader = (succ != nullptr && succ->data.first < e);
      bool chocaizq = (pred != nullptr && pred->data.second > s);

      if (chocader || chocaizq) {
        cout << "NO\n";
      } else {
        tree.insert({s, e});
        cout << "SI\n";
      }

    } else if (op == 2) {
      int s;
      cin >> s;
      tree.erase(tree.search(s));

    } else if (op == 3) {
      int t;
      cin >> t;

      auto cand = tree.predecessor(t);
      if (cand != nullptr && cand->data.second > t) {
        cout << cand->data.first << " " << cand->data.second << "\n";
      } else {
        cout << "LIBRE\n";
      }
    }
  }

  return 0;
}
