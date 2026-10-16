#include <bits/stdc++.h>
using namespace ::std;

template <typename data_type> struct AVL {

  struct TreeNode {
    int height;
    int count = 1;
    long long sum;
    data_type data;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;

    TreeNode(data_type data = data_type(), int height = 0,
             TreeNode *left = nullptr, TreeNode *right = nullptr,
             TreeNode *parent = nullptr)
        : height(height), sum(data), data(data), left(left), right(right),
          parent(parent) {}
  };

  int h(TreeNode *v) { return (v == nullptr ? -1 : v->height); }

  long long sm(TreeNode *v) { return (v == nullptr) ? 0 : v->sum; }

  void update(TreeNode *v) {
    v->height = 1 + max(h(v->left), h(v->right));
    v->sum = (long long)v->count * v->data + sm(v->left) + sm(v->right);
  }

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

  TreeNode *root;

  AVL() { root = nullptr; }

  TreeNode *search(data_type key) {
    TreeNode *current = root;
    while (current != nullptr) {
      if (current->data == key) {
        return current;
      }
      if (current->data > key) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return nullptr;
  }

  TreeNode *min_element(TreeNode *u) {
    if (u == nullptr)
      return nullptr;
    TreeNode *current = u;
    while (current->left != nullptr) {
      current = current->left;
    }
    return current;
  }

  TreeNode *max_element(TreeNode *u) {
    if (u == nullptr)
      return nullptr;
    TreeNode *current = u;
    while (current->right != nullptr) {
      current = current->right;
    }
    return current;
  }

  TreeNode *min_element() { return min_element(root); }

  TreeNode *max_element() { return max_element(root); }

  void insert(data_type value) {
    root = insert(root, value);
    if (root != nullptr)
      root->parent = nullptr;
  }

  TreeNode *insert(TreeNode *u, data_type value) {
    if (u == nullptr) {
      return new TreeNode(value, 0);
    }
    if (value == u->data) {
      u->count++;
      update(u);
      return u;
    }
    if (value < u->data) {
      u->left = insert(u->left, value);
      u->left->parent = u;
    } else {
      u->right = insert(u->right, value);
      u->right->parent = u;
    }
    return rebalance(u);
  }

  void print_inorder() {
    print_subtree_inorder(root);
    cout << endl;
  }

  void print_subtree_inorder(TreeNode *u) {
    if (u == nullptr)
      return;
    print_subtree_inorder(u->left);
    cout << u->data << " ";
    print_subtree_inorder(u->right);
  }

  void print_preorder() {
    print_subtree_preorder(root);
    cout << endl;
  }

  void print_subtree_preorder(TreeNode *u) {
    if (u == nullptr)
      return;
    cout << u->data << " ";
    print_subtree_preorder(u->left);
    print_subtree_preorder(u->right);
  }

  void print_postorder() {
    print_subtree_postorder(root);
    cout << endl;
  }

  void print_subtree_postorder(TreeNode *u) {
    if (u == nullptr)
      return;
    print_subtree_postorder(u->left);
    print_subtree_postorder(u->right);
    cout << u->data << " ";
  }

  TreeNode *successor(TreeNode *x) {
    if (x->right != nullptr) {
      return min_element(x->right);
    }
    TreeNode *y = x->parent;
    while (y != nullptr and y->right == x) {
      x = y;
      y = y->parent;
    }
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

  TreeNode *predecessor(TreeNode *x) {
    if (x->left != nullptr) {
      return max_element(x->left);
    }
    TreeNode *y = x->parent;
    while (y != nullptr and y->left == x) {
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
    if (u->left == nullptr and u->right == nullptr) {
      transplant(u, u->left);
    } else if (u->left != nullptr and u->right != nullptr) {
      TreeNode *succ = successor(u);
      u->data = succ->data;
      u->count = succ->count;
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

  void erase_one(data_type x) {
    TreeNode *u = search(x);
    if (u->count > 1) {
      u->count--;
      while (u != nullptr) {
        update(u);
        u = u->parent;
      }
    } else {
      erase(u);
    }
  }

  // suma de precios < x
  long long suma_menor(int x) {
    long long cant = 0;
    TreeNode *current = root;
    while (current != nullptr) {
      if (current->data < x) {
        cant += sm(current->left) + (long long)current->count * current->data;
        current = current->right;
      } else {
        current = current->left;
      }
    }
    return cant;
  }

  // suma de precios <= x
  long long suma_menor_igual(int x) {
    long long cant = 0;
    TreeNode *current = root;
    while (current != nullptr) {
      if (current->data <= x) {
        cant += sm(current->left) + (long long)current->count * current->data;
        current = current->right;
      } else {
        current = current->left;
      }
    }
    return cant;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(false);
  AVL<int> treate;
  int q;
  cin >> q;
  while (q--) {
    int op, x;
    cin >> op;
    if (op == 1) {
      cin >> x;
      treate.insert(x);
    } else if (op == 2) {
      cin >> x;
      treate.erase_one(x);
    } else {
      int l, r;
      cin >> l >> r;
      cout << treate.suma_menor_igual(r) - treate.suma_menor(l) << '\n';
    }
  }
  return 0;
}
