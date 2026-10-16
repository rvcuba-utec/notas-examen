#include<bits/stdc++.h>
using namespace::std;

template<typename data_type>
struct RBTree {

    enum Color { RED, BLACK };

    struct TreeNode {
        data_type data;
        Color color;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;

        TreeNode(data_type data = data_type(), Color color = RED,
                 TreeNode* left = nullptr, TreeNode* right = nullptr,
                 TreeNode* parent = nullptr) :
                 data(data), color(color), left(left), right(right), parent(parent) {}
    };

    TreeNode* root;
    TreeNode* NIL;

    RBTree() {
        NIL = new TreeNode();
        NIL->color = BLACK;
        NIL->left = NIL->right = NIL->parent = NIL;
        root = NIL;
    }

    bool is_nil(TreeNode* u) { return u == NIL; }

    void rotate_left(TreeNode* x) {
        TreeNode* y = x->right;
        x->right = y->left;
        if (!is_nil(y->left)) y->left->parent = x;
        y->parent = x->parent;
        if (is_nil(x->parent)) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotate_right(TreeNode* x) {
        TreeNode* y = x->left;
        x->left = y->right;
        if (!is_nil(y->right)) y->right->parent = x;
        y->parent = x->parent;
        if (is_nil(x->parent)) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void insert_fixup(TreeNode* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                TreeNode* y = z->parent->parent->right;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
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
                TreeNode* y = z->parent->parent->left;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
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

    void insert(data_type value) {
        TreeNode* z = new TreeNode(value, RED, NIL, NIL, NIL);
        TreeNode* y = NIL;
        TreeNode* x = root;
        while (!is_nil(x)) {
            y = x;
            if (z->data < x->data) x = x->left;
            else x = x->right;
        }
        z->parent = y;
        if (is_nil(y)) root = z;
        else if (z->data < y->data) y->left = z;
        else y->right = z;
        insert_fixup(z);
    }

    void transplant(TreeNode* u, TreeNode* v) {
        if (is_nil(u->parent)) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        v->parent = u->parent;
    }

    TreeNode* min_element(TreeNode* u) {
        while (!is_nil(u->left)) u = u->left;
        return u;
    }

    TreeNode* max_element(TreeNode* u) {
        while (!is_nil(u->right)) u = u->right;
        return u;
    }

    TreeNode* min_element() { return is_nil(root) ? NIL : min_element(root); }
    TreeNode* max_element() { return is_nil(root) ? NIL : max_element(root); }

    void erase_fixup(TreeNode* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                TreeNode* w = x->parent->right;
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
                TreeNode* w = x->parent->left;
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

    void erase(TreeNode* z) {
        TreeNode* y = z;
        TreeNode* x;
        Color y_orig = y->color;
        if (is_nil(z->left)) {
            x = z->right;
            transplant(z, z->right);
        } else if (is_nil(z->right)) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = min_element(z->right);
            y_orig = y->color;
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
        if (y_orig == BLACK) erase_fixup(x);
    }

    void erase(data_type value) {
        TreeNode* current = root;
        while (!is_nil(current)) {
            if (current->data == value) { erase(current); return; }
            if (value < current->data) current = current->left;
            else current = current->right;
        }
    }

    bool search(data_type key) {
        TreeNode* current = root;
        while (!is_nil(current)) {
            if (current->data == key) return true;
            if (key < current->data) current = current->left;
            else current = current->right;
        }
        return false;
    }

    TreeNode* successor(TreeNode* x) {
        if (!is_nil(x->right)) return min_element(x->right);
        TreeNode* y = x->parent;
        while (!is_nil(y) && x == y->right) { x = y; y = y->parent; }
        return y;
    }

    TreeNode* predecessor(TreeNode* x) {
        if (!is_nil(x->left)) return max_element(x->left);
        TreeNode* y = x->parent;
        while (!is_nil(y) && x == y->left) { x = y; y = y->parent; }
        return y;
    }

    void print_inorder() { print_subtree_inorder(root); cout << endl; }
    void print_subtree_inorder(TreeNode* u) {
        if (is_nil(u)) return;
        print_subtree_inorder(u->left);
        cout << u->data << (u->color == RED ? "(R)" : "(B)") << " ";
        print_subtree_inorder(u->right);
    }
};

int main() {
    int n;
    cin >> n;
    RBTree<int> T;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        T.insert(x);
    }
    T.print_inorder();
    return 0;
}
