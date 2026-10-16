#include <algorithm>
#include <bits/stdc++.h>
using namespace ::std;

template <typename data_type> struct BST {

  enum Color { BLACK, RED };

  struct TreeNode {
    data_type data;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    Color color;

    TreeNode(data_type data = data_type(), TreeNode *left = nullptr,
             TreeNode *right = nullptr, TreeNode *parent = nullptr)
        : data(data), left(left), right(right), parent(parent), color(RED) {}
  };

  TreeNode *root;
  TreeNode *Tnil;

  BST() {
    Tnil = new TreeNode();
    Tnil->color = BLACK;
    Tnil->left = Tnil;
    Tnil->right = Tnil;
    Tnil->parent = Tnil;
    root = Tnil;
  }

  void rotate_left(TreeNode *x) {
    TreeNode *y = x->right;
    x->right = y->left;
    if (y->left != Tnil)
      y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == Tnil)
      root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
    y->left = x;
    x->parent = y;
  }

  void rotate_right(TreeNode *y) {
    TreeNode *x = y->left;
    y->left = x->right;
    if (x->right != Tnil)
      x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == Tnil)
      root = x;
    else if (y == y->parent->right)
      y->parent->right = x;
    else
      y->parent->left = x;
    x->right = y;
    y->parent = x;
  }

  bool search(data_type key) {
    TreeNode *current = root;
    while (current != Tnil) {
      if (current->data == key) {
        return true;
      }
      if (current->data > key) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return false;
  }

  TreeNode *min_element(TreeNode *u) {
    if (u == Tnil)
      return Tnil;
    TreeNode *current = u;
    while (current->left != Tnil) {
      current = current->left;
    }
    return current;
  }

  TreeNode *max_element(TreeNode *u) {
    if (u == Tnil)
      return Tnil;
    TreeNode *current = u;
    while (current->right != Tnil) {
      current = current->right;
    }
    return current;
  }

  TreeNode *min_element() { return min_element(root); }

  TreeNode *max_element() { return max_element(root); }

  void insert(data_type value) {
    TreeNode *z = new TreeNode(value, Tnil, Tnil, Tnil);
    TreeNode *y = Tnil;
    TreeNode *x = root;
    while (x != Tnil) {
      y = x;
      if (value < x->data) {
        x = x->left;
      } else {
        x = x->right;
      }
    }
    z->parent = y;
    if (y == Tnil) {
      root = z;
    } else if (z->data < y->data) {
      y->left = z;
    } else {
      y->right = z;
    }
    z->left = Tnil;
    z->right = Tnil;
    z->color = RED;
    insert_fix(z);
  }

  void insert_fix(TreeNode *z) {
    while (z->parent->color == RED) {
      if (z->parent == z->parent->parent->left) {
        TreeNode *t = z->parent->parent->right;
        if (t->color == RED) {
          z->parent->color = BLACK;
          t->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else {
          if (z == z->parent->right) {
            z = z->parent;
            rotate_left(z);
          }
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          rotate_right(z->parent->parent);
        }
      } else {
        TreeNode *t = z->parent->parent->left;
        if (t->color == RED) {
          z->parent->color = BLACK;
          t->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else {
          if (z == z->parent->left) {
            z = z->parent;
            rotate_right(z);
          }
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          rotate_left(z->parent->parent);
        }
      }
    }
    root->color = BLACK;
  }

  void print_inorder() {
    print_subtree_inorder(root);
    cout << endl;
  }

  void print_subtree_inorder(TreeNode *u) {
    if (u == Tnil)
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
    if (u == Tnil)
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
    if (u == Tnil)
      return;
    print_subtree_postorder(u->left);
    print_subtree_postorder(u->right);
    cout << u->data << " ";
  }

  TreeNode *successor(TreeNode *x) {
    if (x->right != Tnil) {
      return min_element(x->right);
    }
    TreeNode *y = x->parent;
    while (y != Tnil and y->right == x) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  TreeNode *predecessor(TreeNode *x) {
    if (x->left != Tnil) {
      return max_element(x->left);
    }
    TreeNode *y = x->parent;
    while (y != Tnil and y->left == x) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  void transplant(TreeNode *u, TreeNode *v) {
    if (u->parent == Tnil) {
      root = v;
    } else if (u->parent->left == u) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  void erase(TreeNode *z) {
    TreeNode *y = z;
    TreeNode *x;
    Color c = y->color;
    if (z->left == Tnil) {
      x = z->right;
      transplant(z, z->right);
    } else if (z->right == Tnil) {
      x = z->left;
      transplant(z, z->left);
    } else {
      y = min_element(z->right);
      c = y->color;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } else {
        transplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    delete z;
    if (c == BLACK) {
      delete_fix(x);
    }
  }

  void delete_fix(TreeNode *x) {
    while (x != root && x->color == BLACK) {
      if (x == x->parent->left) {
        TreeNode *w = x->parent->right;
        if (w->color == RED) {
          w->color = BLACK;
          x->parent->color = RED;
          rotate_left(x->parent);
          w = x->parent->right;
        }
        if (w->left->color == BLACK && w->right->color == BLACK) {
          w->color = RED;
          x = x->parent;
        } else {
          if (w->right->color == BLACK) {
            w->left->color = BLACK;
            w->color = RED;
            rotate_right(w);
            w = x->parent->right;
          }
          w->color = x->parent->color;
          x->parent->color = BLACK;
          w->right->color = BLACK;
          rotate_left(x->parent);
          x = root;
        }
      } else {
        TreeNode *w = x->parent->left;
        if (w->color == RED) {
          w->color = BLACK;
          x->parent->color = RED;
          rotate_right(x->parent);
          w = x->parent->left;
        }
        if (w->right->color == BLACK && w->left->color == BLACK) {
          w->color = RED;
          x = x->parent;
        } else {
          if (w->left->color == BLACK) {
            w->right->color = BLACK;
            w->color = RED;
            rotate_left(w);
            w = x->parent->left;
          }
          w->color = x->parent->color;
          x->parent->color = BLACK;
          w->left->color = BLACK;
          rotate_right(x->parent);
          x = root;
        }
      }
    }
    x->color = BLACK;
  }
};

int main() {
  int n;
  cin >> n;
  BST<int> B;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    B.insert(x);
  }
  B.print_preorder();
  B.print_inorder();
  B.print_postorder();
  return 0;
}
