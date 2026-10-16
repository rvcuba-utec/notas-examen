/*
K. Contar en Rango
Estación meteorológica guarda lecturas de temperatura (enteros, pueden repetirse).
q operaciones:
  1 x: guardar lectura con valor x.
  2 x: descartar UNA lectura con valor x (garantizado: hay al menos una con valor x).
  3 l r: cuántas lecturas guardadas tienen valor entre l y r inclusive.
         Cada lectura cuenta por separado aunque tenga el mismo valor.

Input:
  q (1 <= q <= 5*10^5)
  q líneas: 1 x, 2 x, o 3 l r
  -10^9 <= x <= 10^9, -10^9 <= l <= r <= 10^9

Output: por cada tipo 3: cantidad de lecturas en [l, r].

Example:
Input:
8
1 5
1 3
1 5
3 4 5
1 9
2 5
3 1 10
3 6 8

Output:
2
3
0
*/
#include<bits/stdc++.h>
using namespace::std;

// AVL augmented with subtree_count to support range count queries
// Each node stores (value, occurrences), subtree_count = sum of occurrences in subtree

struct AVL {
    struct TreeNode {
        int height;
        long long data;
        int cnt;          // how many times this value appears
        int subtree_cnt;  // total count in subtree
        TreeNode* left;
        TreeNode* right;

        TreeNode(long long data, int height = 0,
                 TreeNode* left = nullptr, TreeNode* right = nullptr) :
                 data(data), height(height), cnt(1), subtree_cnt(1),
                 left(left), right(right) {}
    };

    TreeNode* root;
    AVL() { root = nullptr; }

    int h(TreeNode* u) { return u == nullptr ? -1 : u->height; }
    int FB(TreeNode* u) { return h(u->left) - h(u->right); }
    int sc(TreeNode* u) { return u == nullptr ? 0 : u->subtree_cnt; }

    void update(TreeNode* u) {
        u->height = 1 + max(h(u->left), h(u->right));
        u->subtree_cnt = u->cnt + sc(u->left) + sc(u->right);
    }

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

    TreeNode* insert(TreeNode* u, long long value) {
        if (u == nullptr) return new TreeNode(value);
        if (value == u->data) { u->cnt++; u->subtree_cnt++; return u; }
        if (value < u->data) u->left = insert(u->left, value);
        else u->right = insert(u->right, value);
        return rebalance(u);
    }

    void insert(long long value) { root = insert(root, value); }

    TreeNode* min_node(TreeNode* u) {
        while (u->left) u = u->left;
        return u;
    }

    TreeNode* erase(TreeNode* u, long long value) {
        if (u == nullptr) return nullptr;
        if (value < u->data) u->left = erase(u->left, value);
        else if (u->data < value) u->right = erase(u->right, value);
        else {
            u->cnt--;
            u->subtree_cnt--;
            if (u->cnt > 0) return u;
            if (u->left == nullptr || u->right == nullptr) {
                TreeNode* child = u->left ? u->left : u->right;
                delete u;
                return child;
            }
            TreeNode* succ = min_node(u->right);
            u->data = succ->data;
            u->cnt = succ->cnt;
            succ->cnt = 1;
            u->right = erase(u->right, succ->data);
            u->subtree_cnt = u->cnt + sc(u->left) + sc(u->right);
            update(u);
            return u;
        }
        return rebalance(u);
    }

    void erase(long long value) { root = erase(root, value); }

    // count elements in [l, r]
    int count_range(TreeNode* u, long long l, long long r) {
        if (u == nullptr) return 0;
        if (r < u->data) return count_range(u->left, l, r);
        if (u->data < l) return count_range(u->right, l, r);
        // l <= u->data <= r
        return u->cnt + count_range(u->left, l, u->data - 1) + count_range(u->right, u->data + 1, r);
    }

    int count_range(long long l, long long r) { return count_range(root, l, r); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    AVL T;
    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            long long x;
            cin >> x;
            T.insert(x);
        } else if (type == 2) {
            long long x;
            cin >> x;
            T.erase(x);
        } else {
            long long l, r;
            cin >> l >> r;
            cout << T.count_range(l, r) << "\n";
        }
    }
    return 0;
}
