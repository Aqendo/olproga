#include "bits/stdc++.h"
#define int int64_t
using namespace std;
vector<vector<int>> g;
vector<int> tin, tout;
vector<vector<int>> binup;
vector<int> cost;
vector<int> p;
struct Node {
    int t, a, b, c;
};
int timer = 0;
void dfs(int x, int par = -1) {
    if (cost[x] == LLONG_MIN) {
        cost[x] = p[x];
    }
    binup[0][x] = (par == -1 ? x : par);
    for (int i = 1; i < 30; ++i) {
        binup[i][x] = binup[i - 1][binup[i - 1][x]];
    }
    tin[x] = timer++;
    for (int u : g[x]) {
        if (u == par) continue;
        cost[u] = cost[x] + p[u];
        dfs(u, x);
    }
    tout[x] = timer;
}
bool is_ancestor(int x, int y) {
    return tin[x] <= tin[y] && tout[y] <= tout[x];
}

int lca(int x, int y) {
    if (is_ancestor(x, y)) return x;
    if (is_ancestor(y, x)) return y;
    for (int i = 29; i >= 0; --i) {
        if (!is_ancestor(binup[i][x], y)) {
            x = binup[i][x];
        }
    }
    return binup[0][x];
}
int get_answer(int a, int b) {
    int lca_vertex = lca(a, b);
    return cost[a] + cost[b] - 2 * cost[lca_vertex] + p[lca_vertex];
}
void solve() {
    int n, q;
    cin >> n >> q;
    tin.assign(n + 1, {});
    tout.assign(n + 1, {});
    cost.assign(n + 1, LLONG_MIN);
    binup.assign(30, vector<int>(n + 1));
    g.assign(n + 1, {});
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    p.assign(n + 1, {});
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
    }
    dfs(1);
    vector<Node> qq(n);
    bool was_other = false;
    for (int i = 0; i < q; ++i) {
        cin >> qq[i].t;
        if (qq[i].t == 1) {
            cin >> qq[i].a >> qq[i].b >> qq[i].c;
            was_other = true;
        } else if (qq[i].t == 2) {
            cin >> qq[i].a >> qq[i].b >> qq[i].c;
            was_other = true;
        } else {
            cin >> qq[i].a >> qq[i].b;
        }
    }
    if (!was_other) {
        for (int i = 0; i < q; ++i) {
            auto [t, a, b, c] = qq[i];
            cout << get_answer(a, b) << endl;
        }
        return;
    }
    for (int i = 0; i < q; ++i) {
        auto [t, a, b, c] = qq[i];
        if (t == 1) {
            int lca_ = lca(a, b);
            while (a != lca_) {
                p[a] = max(p[a], c);
                // cout << "A:" << a << endl;
                a = binup[0][a];
            }
            while (b != lca_) {
                p[b] = max(p[b], c);
                // cout << "B:" << b << endl;
                b = binup[0][b];
            }
            // cout << "LCA_:" << lca_ << endl;
            p[lca_] = max(p[lca_], c);
        } else if (t == 2) {
            int lca_ = lca(a, b);
            while (a != lca_) {
                p[a] = min(p[a], c);
                // cout << "A:" << a << endl;
                a = binup[0][a];
            }
            while (b != lca_) {
                p[b] = min(p[b], c);
                // cout << "B:" << b << endl;
                b = binup[0][b];
            }
            // cout << "LCA_:" << lca_ << endl;
            p[lca_] = min(p[lca_], c);
        } else {
            int lca_ = lca(a, b);
            int answer = 0;
            while (a != lca_) {
                answer += p[a];
                // cout << "A:" << a << ": " << p[a] << endl;
                a = binup[0][a];
            }
            while (b != lca_) {
                answer += p[b];
                // cout << "B:" << b << ": " << p[b] << endl;
                b = binup[0][b];
            }
            // cout << "LCA:" << lca_ << ": " << p[lca_] << endl;
            cout << answer + p[lca_] << '\n';
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
