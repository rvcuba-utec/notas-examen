#include<bits/stdc++.h>
using namespace std;

template<typename data_type>
struct BST {

    struct TreeNode {
        data_type data;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;

        TreeNode(data_type data = data_type(),
                    TreeNode* left = nullptr,
                    TreeNode* right = nullptr,
                    TreeNode* parent = nullptr) :
                    data(data), left(left), right(right), parent(parent) {}
    };

    TreeNode* root;

    BST() {
        root = nullptr;
    }

    ~BST() {
        clear(root);
    }

    void clear(TreeNode* u) {
        if (u == nullptr) return;
        clear(u->left);
        clear(u->right);
        delete u;
    }

    bool search(data_type key) {
        TreeNode* current = root;
        while (current != nullptr) {
            if (current->data == key) {
                return true;
            }
            if (current->data > key) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return false;
    }

    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    TreeNode* max_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current;
    }

    TreeNode* min_element() {
        return min_element(root);
    }

    TreeNode* max_element() {
        return max_element(root);
    }

    void insert(data_type value) {
        if (root == nullptr) {
            root = new TreeNode(value);
            return;
        }
        TreeNode* current = root;
        while (current != nullptr) {
            if (current->data == value) return;
            if (current->data < value) {
                if (current->right != nullptr) {
                    current = current->right;
                }
                else {
                    current->right = new TreeNode(value, nullptr, nullptr, current);
                    break;
                }
            }
            else {
                if (current->left != nullptr) {
                    current = current->left;
                }
                else {
                    current->left = new TreeNode(value, nullptr, nullptr, current);
                    break;
                }
            }
        }
    }

    void print_inorder() {
        print_subtree_inorder(root);
        cout << endl;
    }

    void print_subtree_inorder(TreeNode* u) {
        if (u == nullptr) return;
        print_subtree_inorder(u->left);
        cout << u->data << " ";
        print_subtree_inorder(u->right);
    }

    void print_preorder() {
        print_subtree_preorder(root);
        cout << endl;
    }

    void print_subtree_preorder(TreeNode* u) {
        if (u == nullptr) return;
        cout << u->data << " ";
        print_subtree_preorder(u->left);
        print_subtree_preorder(u->right);
    }

    void print_postorder() {
        print_subtree_postorder(root);
        cout << endl;
    }

    void print_subtree_postorder(TreeNode* u) {
        if (u == nullptr) return;
        print_subtree_postorder(u->left);
        print_subtree_postorder(u->right);
        cout << u->data << " ";
    }

    TreeNode* successor(TreeNode* x) {
        if (x->right != nullptr) {
            return min_element(x->right);
        }
        TreeNode* y = x->parent;
        while (y != nullptr and y->right == x) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    TreeNode* predecessor(TreeNode* x) {
        if (x->left != nullptr) {
            return max_element(x->left);
        }
        TreeNode* y = x->parent;
        while (y != nullptr and y->left == x) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    void transplant(TreeNode* u, TreeNode* v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u->parent->right == u) {
            u->parent->right = v;
        }
        else {
            u->parent->left = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    void erase(TreeNode* u) {
        if (u == nullptr) return;
        
        if (u->left == nullptr and u->right == nullptr) {
            transplant(u, u->left);
            delete u;
        }
        else if (u->left != nullptr and u->right != nullptr) {
            TreeNode* succ = successor(u);
            u->data = succ->data;
            TreeNode* succ_right = succ->right;
            transplant(succ, succ_right);
            delete succ;
        }
        else {
            TreeNode* child = (u->left != nullptr) ? u->left : u->right;
            transplant(u, child);
            delete u;
        }
    }

    void erase(data_type value) {
        TreeNode* current = root;
        while (current != nullptr) {
            if (current->data == value) {
                erase(current);
                return;
            }
            if (current->data > value) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
    }
};
