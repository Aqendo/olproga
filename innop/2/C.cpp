#include <bits/stdc++.h>
using namespace std;
#define int int64_t
struct Info {
    int v, l, dt;
};
vector<vector<Info>> g;
void solve() {
    int n, m;
    cin >> n >> m;
    g.assign(n + 1, {});
    for (int i = 0; i < m; ++i) {
        int u, v, l, dt;
        cin >> u >> v >> l >> dt;
        g[u].push_back({v, l, dt});
    }
    int offset = 30;
    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> pq;
    pq.push({0, 0 + offset, 1});
    vector<vector<int>> dist(n + 1, vector<int>(61, (int)1e18));
    dist[1][0 + offset] = 0;
    while (!pq.empty()) {
        auto [path, temp, vert] = pq.top();
        pq.pop();
        if (dist[vert][temp] < path) continue;
        for (auto [v, l, dt] : g[vert]) {
            if (0 <= temp + dt && temp + dt <= 60 && dist[v][temp + dt] > path + l) {
                dist[v][temp + dt] = path + l;
                pq.push({path + l, temp + dt, v});
            }
        }
    }
    int mn = (int)1e18;
    for (int temp = 0; temp <= 60; ++temp) {
        mn = min(mn, dist[n][temp]);
    }
    cout << (mn == (int)1e18 ? -1 : mn);
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
        if (t != 0) cout << endl;
    }
}