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

  void insert(data_type data) { insert(root, data); }

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

  data_type min_element() { return min_element(root); }

  data_type max_element() { return max_element(root); }

  data_type successor(TreeNode *x) {
    if (x->right != nullptr) {
      return min_element(x->right);
    }
    TreeNode *y = x->parent;
    while (y != nullptr and y->right == x) {
      x = y;
      y = y->parent;
    }
    return y ? y->data : data_type();
  }

  data_type predecessor(TreeNode *x) {
    if (x->left != nullptr) {
      return max_element(x->right);
    }
    TreeNode *y = x->parent;
    while (y != nullptr and y->left == x) {
      x = y;
      y = y->parent;
    }
    return y ? y->data : data_type();
  }

private:
  void insert(TreeNode *root, data_type value) {
    if (root->data == value) {
      return;
    }
    if (value > root->data) {
      if (root->right != nullptr) {
        insert(root->right, value);
      } else {
        root->right = new TreeNode(value, nullptr, nullptr, root);
      }
    }
    if (value < root->data) {
      if (root->left != nullptr) {
        insert(root->left, value);
      } else {
        root->left = new TreeNode(value, nullptr, nullptr, root);
      }
    }
  }
  data_type min_element(TreeNode *root) {
    if (root->left == nullptr) {
      return root->data;
    } else {
      return min_element(root->left);
    }
  }

  data_type max_element(TreeNode *root) {
    if (root->right == nullptr) {
      return root->data;
    } else {
      return max_element(root->right);
    }
  }
};

int main() { return 0; }
