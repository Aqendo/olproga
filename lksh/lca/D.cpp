#include <bits/stdc++.h>

using namespace std;

constexpr int LIMIT_LOG = 32;

vector<int> t_in;
vector<int> t_out;
vector<set<int>> graph;
vector<vector<int>> binup;
int tcounter = 0;

void dfs(int vertex, int parent) {
    t_in[vertex] = tcounter++;
    if (parent == -1) {
        binup[vertex][0] = vertex;
    } else {
        binup[vertex][0] = parent;
    }
    for (int i = 1; i < LIMIT_LOG; ++i) {
        binup[vertex][i] = binup[binup[vertex][i - 1]][i - 1];
    }
    for (int u : graph[vertex]) {
        if (u == parent) continue;
        dfs(u, vertex);
    }
    t_out[vertex] = tcounter++;
}

void init(int n) {
    t_in.assign(n + 1, 0);
    t_out.assign(n + 1, 0);
    graph.assign(n + 1, {});
    binup.assign(n + 1, vector<int>(32));
}

inline bool is_ancestor(int parent, int child) {
    return t_in[parent] <= t_in[child] && t_out[parent] >= t_out[child];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = LIMIT_LOG - 1; i >= 0; --i) {
        if (!is_ancestor(binup[u][i], v)) {
            u = binup[u][i];
        }
    }
    return binup[u][0];
}

void solve() {
    int n;
    cin >> n;
    if (n == 0) exit(0);
    init(n);
    int root = 1;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].insert(v);
        graph[v].insert(u);
    }
    dfs(root, -1);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        char move;
        cin >> move;
        if (move == '!') {
            int to;
            cin >> to;
            root = to;
        } else {
            int u, v;
            cin >> u >> v;
            int ru = lca(root, u);
            int rv = lca(root, v);
            int uv = lca(u, v);
            if (ru == rv) {
                cout << uv << '\n';
            } else if (rv == uv) {
                cout << ru << '\n';
            } else {
                cout << rv << '\n';
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (true) {
        solve();
    }
    return 0;
}