#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;

struct AVL_Array {
  int L[MAXN];
  int R[MAXN];
  int P[MAXN];
  int H[MAXN];
  int val[MAXN];

  int trash[MAXN];
  int trash_sz = 0;
  int node_cnt = 0;
  int root = 0;

  void init() {
    root = 0;
    node_cnt = 0;
    trash_sz = 0;
    H[0] = -1;
    L[0] = R[0] = P[0] = 0;
  }

  int new_node(int v) {
    int u = (trash_sz > 0) ? trash[--trash_sz] : ++node_cnt;
    val[u] = v;
    L[u] = R[u] = P[u] = 0;
    H[u] = 0;
    return u;
  }

  void free_node(int u) {
    trash[trash_sz++] = u;
  }

  int h(int v) { return H[v]; }
  void update(int v) { H[v] = 1 + max(H[L[v]], H[R[v]]); }
  int FB(int v) { return H[L[v]] - H[R[v]]; }

  void add_left_child(int x, int y) {
    L[x] = y;
    if (y != 0) P[y] = x;
  }

  void add_right_child(int x, int y) {
    R[x] = y;
    if (y != 0) P[y] = x;
  }

  int rotate_right(int y) {
    int x = L[y];
    int p = P[y];
    add_left_child(y, R[x]);
    if (p != 0) {
      if (L[p] == y) add_left_child(p, x);
      else add_right_child(p, x);
    } else {
      root = x;
      P[x] = 0;
    }
    add_right_child(x, y);
    update(y);
    update(x);
    return x;
  }

  int rotate_left(int x) {
    int y = R[x];
    int p = P[x];
    add_right_child(x, L[y]);
    if (p != 0) {
      if (L[p] == x) add_left_child(p, y);
      else add_right_child(p, y);
    } else {
      root = y;
      P[y] = 0;
    }
    add_left_child(y, x);
    update(x);
    update(y);
    return y;
  }

  int rebalance(int v) {
    update(v);
    if (FB(v) > 1) {
      if (FB(L[v]) < 0) L[v] = rotate_left(L[v]);
      return rotate_right(v);
    }
    if (FB(v) < -1) {
      if (FB(R[v]) > 0) R[v] = rotate_right(R[v]);
      return rotate_left(v);
    }
    return v;
  }

  int insert(int u, int value) {
    if (u == 0) return new_node(value);
    if (value < val[u]) {
      L[u] = insert(L[u], value);
      P[L[u]] = u;
    } else {
      R[u] = insert(R[u], value);
      P[R[u]] = u;
    }
    return rebalance(u);
  }

  void insert(int value) {
    root = insert(root, value);
    if (root != 0) P[root] = 0;
  }

  int search(int key) {
    int cur = root;
    while (cur != 0) {
      if (val[cur] == key) return cur;
      if (key < val[cur]) cur = L[cur];
      else cur = R[cur];
    }
    return 0;
  }

  int min_element(int u) {
    if (u == 0) return 0;
    while (L[u] != 0) u = L[u];
    return u;
  }

  int max_element(int u) {
    if (u == 0) return 0;
    while (R[u] != 0) u = R[u];
    return u;
  }

  int successor(int x) {
    if (R[x] != 0) return min_element(R[x]);
    int y = P[x];
    while (y != 0 && R[y] == x) {
      x = y;
      y = P[y];
    }
    return y;
  }

  int predecessor(int x) {
    if (L[x] != 0) return max_element(L[x]);
    int y = P[x];
    while (y != 0 && L[y] == x) {
      x = y;
      y = P[y];
    }
    return y;
  }

  void transplant(int u, int v) {
    if (P[u] == 0) {
      root = v;
    } else if (L[P[u]] == u) {
      L[P[u]] = v;
    } else {
      R[P[u]] = v;
    }
    if (v != 0) P[v] = P[u];
    free_node(u);
  }

  void erase(int u) {
    if (u == 0) return;
    int p = P[u];
    if (L[u] == 0 && R[u] == 0) {
      transplant(u, L[u]);
    } else if (L[u] != 0 && R[u] != 0) {
      int succ = successor(u);
      val[u] = val[succ];
      p = P[succ];
      transplant(succ, R[succ]);
    } else {
      if (L[u] != 0) transplant(u, L[u]);
      else transplant(u, R[u]);
    }
    while (p != 0) {
      int parent = P[p];
      if (parent == 0) {
        root = rebalance(p);
        P[root] = 0;
      } else if (L[parent] == p) {
        L[parent] = rebalance(p);
        P[L[parent]] = parent;
      } else {
        R[parent] = rebalance(p);
        P[R[parent]] = parent;
      }
      p = parent;
    }
  }

  void print_inorder(int u) {
    if (u == 0) return;
    print_inorder(L[u]);
    cout << val[u] << " ";
    print_inorder(R[u]);
  }

  void print_inorder() {
    print_inorder(root);
    cout << "\n";
  }
};

AVL_Array tree;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  tree.init();
  int n;
  if (!(cin >> n)) return 0;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    tree.insert(x);
  }
  tree.print_inorder();
  return 0;
}
