#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;

struct RBTree_Array {
  enum Color { BLACK = 0, RED = 1 };

  int L[MAXN];
  int R[MAXN];
  int P[MAXN];
  int color[MAXN];
  int val[MAXN];

  int trash[MAXN];
  int trash_sz = 0;
  int node_cnt = 0;
  int root = 0;

  void init() {
    root = 0;
    node_cnt = 0;
    trash_sz = 0;
    color[0] = BLACK;
    L[0] = R[0] = P[0] = 0;
  }

  int new_node(int v) {
    int u = (trash_sz > 0) ? trash[--trash_sz] : ++node_cnt;
    val[u] = v;
    L[u] = R[u] = P[u] = 0;
    color[u] = RED;
    return u;
  }

  void free_node(int u) {
    trash[trash_sz++] = u;
  }

  void rotate_left(int x) {
    int y = R[x];
    R[x] = L[y];
    if (L[y] != 0) P[L[y]] = x;
    P[y] = P[x];
    if (P[x] == 0) root = y;
    else if (x == L[P[x]]) L[P[x]] = y;
    else R[P[x]] = y;
    L[y] = x;
    P[x] = y;
  }

  void rotate_right(int y) {
    int x = L[y];
    L[y] = R[x];
    if (R[x] != 0) P[R[x]] = y;
    P[x] = P[y];
    if (P[y] == 0) root = x;
    else if (y == R[P[y]]) R[P[y]] = x;
    else L[P[y]] = x;
    R[x] = y;
    P[y] = x;
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

  void insert_fix(int z) {
    while (color[P[z]] == RED) {
      if (P[z] == L[P[P[z]]]) {
        int t = R[P[P[z]]];
        if (color[t] == RED) {
          color[P[z]] = BLACK;
          color[t] = BLACK;
          color[P[P[z]]] = RED;
          z = P[P[z]];
        } else {
          if (z == R[P[z]]) {
            z = P[z];
            rotate_left(z);
          }
          color[P[z]] = BLACK;
          color[P[P[z]]] = RED;
          rotate_right(P[P[z]]);
        }
      } else {
        int t = L[P[P[z]]];
        if (color[t] == RED) {
          color[P[z]] = BLACK;
          color[t] = BLACK;
          color[P[P[z]]] = RED;
          z = P[P[z]];
        } else {
          if (z == L[P[z]]) {
            z = P[z];
            rotate_right(z);
          }
          color[P[z]] = BLACK;
          color[P[P[z]]] = RED;
          rotate_left(P[P[z]]);
        }
      }
    }
    color[root] = BLACK;
  }

  void insert(int value) {
    int z = new_node(value);
    int y = 0;
    int x = root;
    while (x != 0) {
      y = x;
      if (value < val[x]) x = L[x];
      else x = R[x];
    }
    P[z] = y;
    if (y == 0) root = z;
    else if (val[z] < val[y]) L[y] = z;
    else R[y] = z;
    L[z] = 0;
    R[z] = 0;
    color[z] = RED;
    insert_fix(z);
  }

  void transplant(int u, int v) {
    if (P[u] == 0) root = v;
    else if (u == L[P[u]]) L[P[u]] = v;
    else R[P[u]] = v;
    P[v] = P[u];
  }

  void delete_fix(int x) {
    while (x != root && color[x] == BLACK) {
      if (x == L[P[x]]) {
        int w = R[P[x]];
        if (color[w] == RED) {
          color[w] = BLACK;
          color[P[x]] = RED;
          rotate_left(P[x]);
          w = R[P[x]];
        }
        if (color[L[w]] == BLACK && color[R[w]] == BLACK) {
          color[w] = RED;
          x = P[x];
        } else {
          if (color[R[w]] == BLACK) {
            color[L[w]] = BLACK;
            color[w] = RED;
            rotate_right(w);
            w = R[P[x]];
          }
          color[w] = color[P[x]];
          color[P[x]] = BLACK;
          color[R[w]] = BLACK;
          rotate_left(P[x]);
          x = root;
        }
      } else {
        int w = L[P[x]];
        if (color[w] == RED) {
          color[w] = BLACK;
          color[P[x]] = RED;
          rotate_right(P[x]);
          w = L[P[x]];
        }
        if (color[R[w]] == BLACK && color[L[w]] == BLACK) {
          color[w] = RED;
          x = P[x];
        } else {
          if (color[L[w]] == BLACK) {
            color[R[w]] = BLACK;
            color[w] = RED;
            rotate_left(w);
            w = L[P[x]];
          }
          color[w] = color[P[x]];
          color[P[x]] = BLACK;
          color[L[w]] = BLACK;
          rotate_right(P[x]);
          x = root;
        }
      }
    }
    color[x] = BLACK;
  }

  void erase(int z) {
    if (z == 0) return;
    int y = z;
    int x;
    int c = color[y];
    if (L[z] == 0) {
      x = R[z];
      transplant(z, R[z]);
    } else if (R[z] == 0) {
      x = L[z];
      transplant(z, L[z]);
    } else {
      y = min_element(R[z]);
      c = color[y];
      x = R[y];
      if (P[y] == z) {
        P[x] = y;
      } else {
        transplant(y, R[y]);
        R[y] = R[z];
        P[R[y]] = y;
      }
      transplant(z, y);
      L[y] = L[z];
      P[L[y]] = y;
      color[y] = color[z];
    }
    free_node(z);
    if (c == BLACK) delete_fix(x);
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

RBTree_Array rb;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  rb.init();
  int n;
  if (!(cin >> n)) return 0;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    rb.insert(x);
  }
  rb.print_inorder();
  return 0;
}
