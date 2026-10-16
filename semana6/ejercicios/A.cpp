#include <bits/stdc++.h>
using namespace std;

template <typename data_type> struct BST {

  struct TreeNode {
    data_type data;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    TreeNode(data_type data = data_type(), TreeNode *left = nullptr,
             TreeNode *right = nullptr, TreeNode *parent = nullptr)
        : data(data), left(left), right(right), parent(parent) {}
  };

  TreeNode *root;

  BST() { root = new TreeNode(); }

  BST(TreeNode *node) : root(node) {}

  void insert(data_type value) {
    TreeNode *current = root;
    if (root == nullptr) {
      root = new TreeNode(value);
      return;
    }
    while (current != nullptr) {
      if (current->data == value)
        return;
      if (current->data < value) {
        if (current->right != nullptr) {
          current = current->right;
        } else {
          current->right = new TreeNode(value);
          break;
        }
      }
      if (current->data > value) {
        if (current->left != nullptr) {
          current = current->left;
        } else {
          current->left = new TreeNode(value);
          break;
        }
      }
    }
  }

  bool search(data_type key) {
    TreeNode *current = root;
    while (current != nullptr) {
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

  data_type min_element() {
    TreeNode *current = root;
    while (current->left != nullptr) {
      current = current->left;
    }
    return current->data;
  }

  data_type max_element() {
    TreeNode *current = root;
    while (current->right != nullptr) {
      current = current->right;
    }
    return current->data;
  }

  void print_inorder() { print_subtree_inorder(root); }
  void print_preorder() { print_subtree_preorder(root); }
  void print_postorder() { print_subtree_postorder(root); }

  void print_subtree_inorder(TreeNode *u) {
    if (u == nullptr)
      return;
    print_subtree_inorder(u->left);
    cout << u->data << " ";
    print_subtree_inorder(u->right);
  }
  void print_subtree_preorder(TreeNode *u) {
    if (u == nullptr)
      return;
    cout << u->data << " ";
    print_subtree_preorder(u->left);
    print_subtree_preorder(u->right);
  }

  void print_subtree_postorder(TreeNode *u) {
    if (u == nullptr)
      return;
    print_subtree_postorder(u->left);
    print_subtree_postorder(u->right);
    cout << u->data << " ";
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(false); // Fast I/O con cin/cout
  BST<int> tree(nullptr);
  int t;
  cin >> t;
  while (t--) {
    int x;
    cin >> x;
    tree.insert(x);
  }
  tree.print_preorder();
  cout << endl;
  tree.print_inorder();
  cout << endl;
  tree.print_postorder();
}
