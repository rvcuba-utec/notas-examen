#include <bits/stdc++.h>
using namespace ::std;

template <typename data_type> struct AVL {

  struct TreeNode {
    int height;
    data_type data;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;

    TreeNode(data_type data = data_type(), int height = 0,
             TreeNode *left = nullptr, TreeNode *right = nullptr,
             TreeNode *parent = nullptr)
        : height(height), data(data), left(left), right(right), parent(parent) {
    }
  };

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
    cout << "buscando predecesor de " << x->data << '\n';
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

  TreeNode *successor(int x) {
    TreeNode *current = root;
    TreeNode *succesor = nullptr;
    while (current != nullptr) {
      if (current->data >= x) {
        succesor = current;
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return succesor;
  }

  TreeNode *predecessor(int x) {
    TreeNode *current = root;
    TreeNode *predecesor = nullptr;
    while (current != nullptr) {
      if (current->data <= x) {
        predecesor = current;
        current = current->right;
      } else {
        current = current->left;
      }
    }
    return predecesor;
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
  int q;
  AVL<int> estaciones;
  cin >> q;
  while (q--) {
    int op;
    int x;
    cin >> op >> x;
    if (op == 1) {
      estaciones.insert(x);
    } else if (op == 2) {
      estaciones.erase(estaciones.search(x));
    } else {
      if (estaciones.predecessor(x) == nullptr) {
        cout << estaciones.successor(x)->data << '\n';
      } else if (estaciones.successor(x) == nullptr) {
        cout << estaciones.predecessor(x)->data << '\n';
      } else {
        int ant = estaciones.predecessor(x)->data;
        int pos = estaciones.successor(x)->data;
        cout << (x - ant <= pos - x ? ant : pos) << '\n';
      }
    }
  }
}
