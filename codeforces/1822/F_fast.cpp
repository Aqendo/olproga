#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<vector<int>> g;
vector<int> dp, answer;

void countroot(int x, int p = -1) {
    int mx = 0;
    for (int u : g[x]) {
        if (u != p) {
            countroot(u, x);
            mx = max(mx, dp[u]);
        }
    }
    dp[x] = mx + 1;
}

void counteverything(int x, int p = -1, int mx_nad = 0) {
    if (g[x].size() == 1) {
        if (p == -1) {
            answer[x] = dp[x] - 1;
            for (int u : g[x]) {
                if (u != p) {
                    counteverything(u, x, 1);
                }
            }
            return;
        } else {
            answer[x] = mx_nad;
            return;
        }
    }
    if (g[x].empty()) return;
    auto get = [&](int vert) {
        return vert == p ? mx_nad : dp[vert];
    };
    int mx = g[x][0];
    int smx = g[x][1];
    if (get(mx) < get(smx)) swap(mx, smx);
    for (int i = 2; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (get(u) > get(mx)) {
            smx = mx;
            mx = u;
        } else if (get(u) > get(smx)) {
            smx = u;
        }
    }
    answer[x] = get(mx);
    for (int u : g[x]) {
        if (u != p) {
            if (u == mx) {
                counteverything(u, x, get(smx) + 1);
            } else {
                counteverything(u, x, get(mx) + 1);
            }
        }
    }
}

void solve() {
    int n, k, c;
    cin >> n >> k >> c;
    g.assign(n + 1, {});
    dp.assign(n + 1, {});
    answer.assign(n + 1, {});
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    countroot(1);
    counteverything(1);
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
        // cout << i << ": " << answer[i] << ' ' << dist[i] << endl;
        mx = max(mx, answer[i] * k - dist[i] * c);
    }
    cout << mx << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}