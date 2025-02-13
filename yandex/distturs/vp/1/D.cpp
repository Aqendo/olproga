#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<vector<int>> g;
vector<int> dp;
pair<int, int> getmx(int x, int p = -1) {
    pair<int, int> res = {0, x};
    for (int u : g[x]) {
        if (u != p) {
            auto r = getmx(u, x);
            if (r.first + 1 > res.first) {
                res = r;
                res.first++;
            }
        }
    }
    return res;
}
int countdp(int x, int p = -1) {
    for (int u : g[x]) {
        if (u != p) {
            dp[x] = max(dp[x], countdp(u, x) + 1);
        }
    }
    return dp[x];
}

void solve() {
    int n, k;
    cin >> n >> k;
    g.assign(n + 1, {});
    dp.assign(n + 1, {});

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    auto [mx, v] = getmx(1);
    auto [mx2, vv] = getmx(v);
    if (k == 1) {
        cout << mx2 * 10 << '\n';
        return;
    }
    countdp(v);
    vector<bool> is_diam(n + 1, 0);
    is_diam[v] = true;
    int parent = -1;
    int already = (mx2 * 2) * 10;
    int answer = 2 * mx2 * 10;
    while (v != -1) {
        int next = -1;
        for (int u : g[v]) {
            if (u != parent) {
                if (next == -1 || dp[u] > dp[next]) next = u;
            }
        }
        for (int u : g[v]) {
            if (u != parent) {
                if (u != next) {
                    answer = max(answer, already + 2 * dp[u] * 10);
                }
            }
        }
        parent = v;
        v = next;
    }
    cout << answer << '\n';
    // v  - start
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}
