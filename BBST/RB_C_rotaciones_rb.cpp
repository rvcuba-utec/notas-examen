/*
RB-C. Rotaciones en Red-Black Tree (inserción)
Insertar n claves en un RB tree vacío. Después de cada inserción indicar:
  - cuántas rotaciones se hicieron (cada rotate_left/rotate_right = 1 rotación)
  - el color de la raíz actual

En la inserción RB, las recoloraciones (cambios de color) NO cuentan como rotaciones.
Solo las rotaciones geométricas cuentan.

Input:
  n (1 <= n <= 2*10^5)
  n enteros distintos

Output:
  n líneas: rotaciones color_raiz (R o N)

Example:
Input:
5
10 20 30 40 50

Output:
0 N
0 N
1 N
0 N
1 N
*/
#include<bits/stdc++.h>
using namespace::std;

int rot_count;

struct RBTree {
    enum Color { RED, BLACK };

    struct TreeNode {
        int data;
        Color color;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
        TreeNode(int data = 0, Color color = RED,
                 TreeNode* left = nullptr, TreeNode* right = nullptr,
                 TreeNode* parent = nullptr) :
                 data(data), color(color), left(left), right(right), parent(parent) {}
    };

    TreeNode* root;
    TreeNode* NIL;

    RBTree() {
        NIL = new TreeNode(0, BLACK, nullptr, nullptr, nullptr);
        NIL->left = NIL->right = NIL->parent = NIL;
        root = NIL;
    }

    bool is_nil(TreeNode* u) { return u == NIL; }

    void rotate_left(TreeNode* x) {
        rot_count++;
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
        rot_count++;
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
                    if (z == z->parent->right) { z = z->parent; rotate_left(z); }
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
                    if (z == z->parent->left) { z = z->parent; rotate_right(z); }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotate_left(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void insert(int value) {
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
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    RBTree T;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        rot_count = 0;
        T.insert(x);
        cout << rot_count << " " << (T.root->color == RBTree::BLACK ? "N" : "R") << "\n";
    }
    return 0;
}
