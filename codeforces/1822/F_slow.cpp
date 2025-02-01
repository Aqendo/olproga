#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<vector<int>> g;
vector<int> dp, answer;

int dfs(int x, int p = -1) {
    int mx = 0;
    for (int u : g[x]) {
        if (u != p) {
            mx = max(mx, dfs(u, x));
        }
    }
    return mx + 1;
}

void solve() {
    int n, k, c;
    cin >> n >> k >> c;
    g.assign(n + 1, {});
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> dist(n + 1, INT_MAX);
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int u : g[x]) {
            if (dist[x] + 1 < dist[u]) {
                q.push(u);
                dist[u] = dist[x] + 1;
            }
        }
    }
    int mx = 0;
    for (int i = 1; i <= n; ++i) {
        mx = max(mx, (dfs(i) - 1) * k - dist[i] * c);
    }
    cout << mx << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}