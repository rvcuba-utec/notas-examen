/*
E. Contar Rotaciones
AVL vacío, q operaciones:
  1 x: INSERTAR x (x no está en el árbol)
  2 x: ELIMINAR x (x está en el árbol; si no tiene hijo izq, su hijo der toma su lugar;
       si no tiene hijo der, su hijo izq toma su lugar; si tiene ambos, toma la clave de su sucesor)
En ambas operaciones, al volver hacia la raíz se REBALANCEA cada nodo v:
  si FB(v) > 1: ROTAR-DERECHA en v, precedida de ROTAR-IZQUIERDA en v.izq si FB(v.izq) < 0
  si FB(v) < -1: ROTAR-IZQUIERDA en v, precedida de ROTAR-DERECHA en v.der si FB(v.der) > 0
Después de cada operación: imprimir cuántas rotaciones se hicieron y la altura del árbol.
Altura de árbol vacío = -1, un nodo = 0.

Input:
  q (1 <= q <= 3*10^5)
  q líneas: 1 x o 2 x (1 <= x <= 10^9)

Output:
  q líneas: rotaciones_hechas altura_avl

Example:
Input:
10
1 10
1 20
1 30
1 40
1 35
2 10
2 40
2 20
2 35
2 30

Output:
0 0
0 1
1 1
0 2
2 2
2 1
0 1
0 0
0 0
0 -1
*/
#include<bits/stdc++.h>
using namespace::std;

int rot_count;

struct AVL {

    struct TreeNode {
        int height;
        int data;
        TreeNode* left;
        TreeNode* right;

        TreeNode(int data = 0, int height = 0,
                    TreeNode* left = nullptr, TreeNode* right = nullptr) :
                    data(data), height(height), left(left), right(right) {}
    };

    TreeNode* root;
    AVL() { root = nullptr; }

    void update(TreeNode* u) {
        u->height = 1 + max(h(u->left), h(u->right));
    }

    int h(TreeNode* u) { return u == nullptr ? -1 : u->height; }
    int FB(TreeNode* u) { return h(u->left) - h(u->right); }

    TreeNode* rotate_left(TreeNode* u) {
        rot_count++;
        TreeNode* v = u->right;
        u->right = v->left;
        v->left = u;
        update(u); update(v);
        return v;
    }

    TreeNode* rotate_right(TreeNode* u) {
        rot_count++;
        TreeNode* v = u->left;
        u->left = v->right;
        v->right = u;
        update(u); update(v);
        return v;
    }

    TreeNode* rebalance(TreeNode* u) {
        update(u);
        if (FB(u) > 1) {
            if (FB(u->left) < 0) u->left = rotate_left(u->left);
            return rotate_right(u);
        }
        if (FB(u) < -1) {
            if (FB(u->right) > 0) u->right = rotate_right(u->right);
            return rotate_left(u);
        }
        return u;
    }

    TreeNode* min_element(TreeNode* u) {
        while (u->left != nullptr) u = u->left;
        return u;
    }

    TreeNode* insert(TreeNode* u, int value) {
        if (u == nullptr) return new TreeNode(value, 0);
        if (value < u->data) u->left = insert(u->left, value);
        else u->right = insert(u->right, value);
        return rebalance(u);
    }

    void insert(int value) { root = insert(root, value); }

    TreeNode* erase(TreeNode* u, int value) {
        if (u == nullptr) return nullptr;
        if (value < u->data) u->left = erase(u->left, value);
        else if (u->data < value) u->right = erase(u->right, value);
        else {
            if (u->left == nullptr || u->right == nullptr) {
                TreeNode* child = (u->left != nullptr) ? u->left : u->right;
                delete u;
                return child;
            }
            TreeNode* succ = min_element(u->right);
            u->data = succ->data;
            u->right = erase(u->right, succ->data);
        }
        return rebalance(u);
    }

    void erase(int value) { root = erase(root, value); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int q;
    cin >> q;
    AVL T;
    while (q--) {
        int type, x;
        cin >> type >> x;
        rot_count = 0;
        if (type == 1) T.insert(x);
        else T.erase(x);
        int h = (T.root == nullptr) ? -1 : T.root->height;
        cout << rot_count << " " << h << "\n";
    }
    return 0;
}
