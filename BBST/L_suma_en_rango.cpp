/*
L. Suma en Rango
Tienda lleva registro de precios (pueden repetirse). q operaciones:
  1 x: llega un producto de precio x.
  2 x: se vende UN producto de precio x (garantizado: hay al menos uno).
  3 l r: suma de los precios de todos los productos cuyo precio está en [l, r] inclusive.
         Cada producto suma su precio aunque haya otros con el mismo precio.
         La suma puede no caber en 32 bits.

Input:
  q (1 <= q <= 5*10^5)
  q líneas: 1 x, 2 x, o 3 l r
  1 <= x <= 10^9, 1 <= l <= r <= 10^9

Output: por cada tipo 3: la suma (puede ser > 2^32, usar long long).

Example:
Input:
7
1 10
1 20
1 10
3 5 15
1 30
2 10
3 10 30

Output:
20
60
*/
#include<bits/stdc++.h>
using namespace::std;

// AVL augmented with subtree_sum and subtree_cnt for range sum queries

struct AVL {
    struct TreeNode {
        int height;
        long long data;
        int cnt;
        int subtree_cnt;
        long long subtree_sum;
        TreeNode* left;
        TreeNode* right;

        TreeNode(long long data, int height = 0,
                 TreeNode* left = nullptr, TreeNode* right = nullptr) :
                 data(data), height(height), cnt(1), subtree_cnt(1),
                 subtree_sum(data), left(left), right(right) {}
    };

    TreeNode* root;
    AVL() { root = nullptr; }

    int h(TreeNode* u) { return u == nullptr ? -1 : u->height; }
    int FB(TreeNode* u) { return h(u->left) - h(u->right); }
    int sc(TreeNode* u) { return u == nullptr ? 0 : u->subtree_cnt; }
    long long ss(TreeNode* u) { return u == nullptr ? 0LL : u->subtree_sum; }

    void update(TreeNode* u) {
        u->height = 1 + max(h(u->left), h(u->right));
        u->subtree_cnt = u->cnt + sc(u->left) + sc(u->right);
        u->subtree_sum = (long long)u->cnt * u->data + ss(u->left) + ss(u->right);
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
        if (value == u->data) {
            u->cnt++;
            u->subtree_cnt++;
            u->subtree_sum += value;
            return u;
        }
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
            u->subtree_sum -= value;
            if (u->cnt > 0) return u;
            if (u->left == nullptr || u->right == nullptr) {
                TreeNode* child = u->left ? u->left : u->right;
                delete u;
                return child;
            }
            TreeNode* succ = min_node(u->right);
            long long old_data = u->data;
            u->data = succ->data;
            u->cnt = succ->cnt;
            succ->cnt = 1;
            u->right = erase(u->right, succ->data);
            update(u);
            return u;
        }
        return rebalance(u);
    }

    void erase(long long value) { root = erase(root, value); }

    // sum of elements in [l, r]
    long long sum_range(TreeNode* u, long long l, long long r) {
        if (u == nullptr) return 0;
        if (r < u->data) return sum_range(u->left, l, r);
        if (u->data < l) return sum_range(u->right, l, r);
        return (long long)u->cnt * u->data
             + sum_range(u->left, l, u->data - 1)
             + sum_range(u->right, u->data + 1, r);
    }

    long long sum_range(long long l, long long r) { return sum_range(root, l, r); }
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
            cout << T.sum_range(l, r) << "\n";
        }
    }
    return 0;
}
