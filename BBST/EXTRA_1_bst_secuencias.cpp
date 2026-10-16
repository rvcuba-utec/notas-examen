/*
EXTRA-1. Secuencias de BST
Dado un árbol BST (por preorden), responder consultas:
  1. ¿Cuántos elementos hay en el rango [l, r]?
  2. ¿Cuál es el k-ésimo elemento menor?
  3. ¿Cuál es el sucesor de x? (menor elemento > x)
  4. ¿Cuál es el predecesor de x? (mayor elemento < x)

Usa un AVL augmentado con subtree_cnt.

Input:
  n q (1 <= n,q <= 2*10^5)
  n enteros distintos (secuencia de inserción)
  q consultas: tipo argumentos
    1 l r → contar en [l,r]
    2 k   → k-ésimo menor
    3 x   → sucesor de x (o -1 si no existe)
    4 x   → predecesor de x (o -1 si no existe)

Output: una línea por consulta.

Example:
Input:
6 6
10 20 5 15 25 30
1 10 25
2 3
3 20
4 20
3 30
4 5

Output:
4
15
25
15
-1
-1
*/
#include<bits/stdc++.h>
using namespace::std;

struct AVL {
    struct TreeNode {
        int height, cnt, data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int d) : height(0), cnt(1), data(d), left(nullptr), right(nullptr) {}
    };

    TreeNode* root = nullptr;

    int h(TreeNode* u) { return u ? u->height : -1; }
    int cnt(TreeNode* u) { return u ? u->cnt : 0; }
    int FB(TreeNode* u) { return h(u->left) - h(u->right); }

    void update(TreeNode* u) {
        u->height = 1 + max(h(u->left), h(u->right));
        u->cnt = 1 + cnt(u->left) + cnt(u->right);
    }

    TreeNode* rotate_left(TreeNode* u) {
        auto v = u->right; u->right = v->left; v->left = u;
        update(u); update(v); return v;
    }
    TreeNode* rotate_right(TreeNode* u) {
        auto v = u->left; u->left = v->right; v->right = u;
        update(u); update(v); return v;
    }
    TreeNode* rebalance(TreeNode* u) {
        update(u);
        if (FB(u) > 1) { if (FB(u->left) < 0) u->left = rotate_left(u->left); return rotate_right(u); }
        if (FB(u) < -1) { if (FB(u->right) > 0) u->right = rotate_right(u->right); return rotate_left(u); }
        return u;
    }

    TreeNode* insert(TreeNode* u, int v) {
        if (!u) return new TreeNode(v);
        if (v < u->data) u->left = insert(u->left, v);
        else u->right = insert(u->right, v);
        return rebalance(u);
    }
    void insert(int v) { root = insert(root, v); }

    // count in [l, r]
    int count_range(TreeNode* u, int l, int r) {
        if (!u) return 0;
        if (r < u->data) return count_range(u->left, l, r);
        if (u->data < l) return count_range(u->right, l, r);
        return 1 + count_range(u->left, l, u->data-1) + count_range(u->right, u->data+1, r);
    }
    int count_range(int l, int r) { return count_range(root, l, r); }

    // k-th smallest (1-indexed)
    int kth(TreeNode* u, int k) {
        int lc = cnt(u->left);
        if (k == lc + 1) return u->data;
        if (k <= lc) return kth(u->left, k);
        return kth(u->right, k - lc - 1);
    }
    int kth(int k) { return kth(root, k); }

    // successor of x (smallest element > x)
    int successor(TreeNode* u, int x, int best) {
        if (!u) return best;
        if (u->data > x) return successor(u->left, x, u->data);
        return successor(u->right, x, best);
    }
    int successor(int x) { return successor(root, x, -1); }

    // predecessor of x (largest element < x)
    int predecessor(TreeNode* u, int x, int best) {
        if (!u) return best;
        if (u->data < x) return predecessor(u->right, x, u->data);
        return predecessor(u->left, x, best);
    }
    int predecessor(int x) { return predecessor(root, x, -1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    AVL T;
    for (int i = 0; i < n; ++i) { int x; cin >> x; T.insert(x); }

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int l, r; cin >> l >> r;
            cout << T.count_range(l, r) << "\n";
        } else if (type == 2) {
            int k; cin >> k;
            cout << T.kth(k) << "\n";
        } else if (type == 3) {
            int x; cin >> x;
            cout << T.successor(x) << "\n";
        } else {
            int x; cin >> x;
            cout << T.predecessor(x) << "\n";
        }
    }
    return 0;
}
