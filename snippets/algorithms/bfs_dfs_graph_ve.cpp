// ============================================================
// Grafos: BFS y DFS
// ============================================================
// BFS: O(V + E) tiempo, O(V) espacio
// DFS: O(V + E) tiempo, O(V) espacio
//
// Uso: Recorrido de grafos, componentes conexos, camino más
//      corto en grafos sin peso (BFS), detección de ciclos, etc.
//
// Aplicaciones:
//   - Camino más corto sin pesos (BFS)
//   - Componentes conexos
//   - Bipartiteness check (BFS)
//   - Topological sort (DFS)
//   - Detección de ciclos (DFS)
//   - Flood fill
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------
// BFS - Camino más corto sin pesos
// -----------------------------------------------
vector<int> dist;
vector<int> parent;

void bfs(vector<vector<int>> &adj, int source) {
    int n = adj.size();
    dist.assign(n, -1);
    parent.assign(n, -1);

    queue<int> q;
    dist[source] = 0;
    q.push(source);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }
}

// Reconstruir camino desde source hasta target
vector<int> get_path(int target) {
    vector<int> path;
    for (int v = target; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

// -----------------------------------------------
// DFS iterativo
// -----------------------------------------------
vector<int> dfs_iterative(vector<vector<int>> &adj, int source) {
    int n = adj.size();
    vector<bool> visited(n, false);
    vector<int> order;

    stack<int> st;
    st.push(source);

    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (visited[u]) continue;
        visited[u] = true;
        order.push_back(u);

        for (int v : adj[u]) {
            if (!visited[v]) st.push(v);
        }
    }
    return order;
}

// -----------------------------------------------
// DFS recursivo
// -----------------------------------------------
vector<bool> visited;
vector<int> dfs_order;

void dfs(vector<vector<int>> &adj, int u) {
    visited[u] = true;
    dfs_order.push_back(u);
    for (int v : adj[u]) {
        if (!visited[v]) dfs(adj, v);
    }
}

// -----------------------------------------------
// Contar componentes conexos
// -----------------------------------------------
int count_components(vector<vector<int>> &adj) {
    int n = adj.size();
    visited.assign(n, false);
    dfs_order.clear();
    int components = 0;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(adj, i);
            ++components;
        }
    }
    return components;
}

// -----------------------------------------------
// Topological Sort (DFS, grafos dirigidos acíclicos)
// -----------------------------------------------
vector<int> topo_order;
vector<int> color; // 0=white, 1=gray, 2=black
bool has_cycle;

void topo_dfs(vector<vector<int>> &adj, int u) {
    color[u] = 1; // Gray (en proceso)
    for (int v : adj[u]) {
        if (color[v] == 1) { has_cycle = true; return; }
        if (color[v] == 0) topo_dfs(adj, v);
        if (has_cycle) return;
    }
    color[u] = 2; // Black (terminado)
    topo_order.push_back(u);
}

vector<int> topological_sort(vector<vector<int>> &adj) {
    int n = adj.size();
    color.assign(n, 0);
    topo_order.clear();
    has_cycle = false;

    for (int i = 0; i < n; ++i) {
        if (color[i] == 0) topo_dfs(adj, i);
    }

    reverse(topo_order.begin(), topo_order.end());
    return topo_order; // Vacío si hay ciclo
}

// -----------------------------------------------
// Check Bipartite (BFS)
// -----------------------------------------------
bool is_bipartite(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> color(n, -1);

    for (int start = 0; start < n; ++start) {
        if (color[start] != -1) continue;
        queue<int> q;
        q.push(start);
        color[start] = 0;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    q.push(v);
                } else if (color[v] == color[u]) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    // Grafo no dirigido: 0-1, 1-2, 0-3, 2-5, 4-5
    int n = 6;
    vector<vector<int>> adj(n);
    auto add_edge = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };
    add_edge(0, 1); add_edge(1, 2); add_edge(0, 3);
    add_edge(2, 5); add_edge(4, 5);

    bfs(adj, 0);
    cout << "Distances from 0: ";
    for (int i = 0; i < n; ++i) cout << dist[i] << " ";
    cout << '\n';

    auto path = get_path(4);
    cout << "Path 0 -> 4: ";
    for (int v : path) cout << v << " ";
    cout << '\n';

    cout << "Components: " << count_components(adj) << '\n';
    cout << "Bipartite? " << (is_bipartite(adj) ? "Yes" : "No") << '\n';

    // Topological sort (grafo dirigido)
    vector<vector<int>> dag(4);
    dag[0].push_back(1); dag[0].push_back(2);
    dag[1].push_back(3); dag[2].push_back(3);
    auto topo = topological_sort(dag);
    cout << "Topological order: ";
    for (int v : topo) cout << v << " ";
    cout << '\n';

    return 0;
}
