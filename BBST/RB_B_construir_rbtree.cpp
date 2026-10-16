/*
RB-B. Construir un Red-Black Tree
Insertar n claves distintas en un RB tree vacío (en el orden dado).
Después de cada inserción, imprimir:
  - la clave en la raíz
  - el color de la raíz (siempre N)
  - la black-height del árbol (número de nodos negros en cualquier camino raíz→hoja,
    sin contar el nodo NIL pero contando la raíz)

Input:
  n (1 <= n <= 2*10^5)
  n enteros distintos a1..an

Output:
  n líneas: raiz black_height

Example:
Input:
7
10 20 30 40 50 25 35

Output:
10 1
20 1
20 2
20 2
30 2
30 2
30 2
*/
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

    int black_height(TreeNode* u) {
        if (is_nil(u)) return 0;
        int bh = black_height(u->left);
        return bh + (u->color == BLACK ? 1 : 0);
    }

    int black_height() { return black_height(root); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    RBTree<int> T;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        T.insert(x);
        cout << T.root->data << " " << T.black_height() << "\n";
    }
    return 0;
}
