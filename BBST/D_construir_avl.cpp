/*
D. Construir un AVL
Insertar n claves distintas a1..an en un AVL vacío, en orden.
Después de cada inserción, imprimir la altura del árbol y la clave en la raíz.
La altura de un árbol con un solo nodo es 0.

Input:
  n (1 <= n <= 2*10^5)
  n enteros distintos a1..an (1 <= ai <= 10^9)

Output:
  n líneas: altura_del_AVL clave_raíz (después de insertar a_i)

Example:
Input:
6
10 20 30 40 50 25

Output:
0 10
1 10
1 20
2 20
2 20
2 30
*/
#include<bits/stdc++.h>
using namespace::std;

template<typename data_type>
struct AVL {

    struct TreeNode {
        int height;
        data_type data;
        TreeNode* left;
        TreeNode* right;

        TreeNode(data_type data = data_type(), int height = 0,
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
        TreeNode* v = u->right;
        u->right = v->left;
        v->left = u;
        update(u); update(v);
        return v;
    }

    TreeNode* rotate_right(TreeNode* u) {
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

    TreeNode* insert(TreeNode* u, data_type value) {
        if (u == nullptr) return new TreeNode(value, 0);
        if (value < u->data) u->left = insert(u->left, value);
        else u->right = insert(u->right, value);
        return rebalance(u);
    }

    void insert(data_type value) {
        root = insert(root, value);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    AVL<int> T;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        T.insert(x);
        cout << T.h(T.root) << " " << T.root->data << "\n";
    }
    return 0;
}
