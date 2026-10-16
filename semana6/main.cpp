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

  void print_subtree_inorder(TreeNode *u) {
    if (u == nullptr)
      return;
    print_subtree_inorder(u->left);
    cout << u->data << " ";
    print_subtree_inorder(u->right);
  }
};

int main() {
  BST<int> B(nullptr);
  B.insert(7);
  B.insert(4);
  B.insert(10);
  B.insert(10);
  B.insert(9);
  B.insert(1);
  B.insert(3);
  cout << B.min_element() << " " << B.max_element() << endl;
  B.print_inorder();
  cout << '\n';
  return 0;
}
