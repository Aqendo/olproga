#include <bits/stdc++.h>

using namespace std;

constexpr int MAX_LOG = 29;
vector<vector<pair<int, int>>> g;
vector<vector<int>> binup_v;
vector<vector<int>> binup_min;
vector<int> tin, tout, depth;
int timer = 0;

void dfs(int x, int p, int w, int depth_) {
    depth[x] = depth_;
    tin[x] = timer++;
    binup_v[0][x] = p;
    binup_min[0][x] = w;
    for (auto [u, w] : g[x]) {
        if (u != p) {
            dfs(u, x, w, depth_ + 1);
        }
    }
    tout[x] = timer++;
}

pair<int, int> la(int v, int d) {
    int mn = INT_MAX;
    for (int power = MAX_LOG - 1; power >= 0; --power) {
        if ((1 << power) <= d) {
            mn = min(mn, binup_min[power][v]);
            v = binup_v[power][v];
            d -= (1 << power);
        }
    }
    return {v, mn};
}

pair<int, int> lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    auto [u_, mn] = la(u, depth[u] - depth[v]);
    u = u_;
    if (u == v) {
        return {u, mn};
    }
    for (int power = MAX_LOG - 1; power >= 0; power--) {
        if (binup_v[power][u] != binup_v[power][v]) {
            mn = min({mn, binup_min[power][v], binup_min[power][u]});
            u = binup_v[power][u];
            v = binup_v[power][v];
        }
    }
    mn = min({mn, binup_min[0][v], binup_min[0][u]});
    return {binup_v[0][v], mn};
}

void init(int n) {
    g.assign(n + 1, {});
    binup_v.assign(MAX_LOG, vector<int>(n + 1));
    binup_min.assign(MAX_LOG, vector<int>(n + 1));
    tin.assign(n + 1, {});
    tout.assign(n + 1, {});
    depth.assign(n + 1, {});
}

void solve() {
    int n;
    cin >> n;

    init(n);

    for (int i = 0; i < n - 1; ++i) {
        int p, w;
        cin >> p >> w;
        g[i + 2].emplace_back(p, w);
        g[p].emplace_back(i + 2, w);
    }

    dfs(1, 1, INT_MAX, 1);

    for (int i = 1; i <= n; ++i) {
        for (int power = 1; power <= MAX_LOG - 1; ++power) {
            binup_min[power][i] = min(binup_min[power - 1][i], binup_min[power - 1][binup_v[power - 1][i]]);
            binup_v[power][i] = binup_v[power - 1][binup_v[power - 1][i]];
        }
    }

    int q;
    cin >> q;

    for (int qq = 0; qq < q; ++qq) {
        int u, v;
        cin >> u >> v;
        auto [lca_, mn] = lca(u, v);
        cout << mn << '\n';
    }
}

signed main() {
    cout << boolalpha;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}