#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<vector<int>> g;
vector<array<int, 2>> dp;
void dfs(int x, int p = -1) {
    if (g[x].size() == 0 || (dp[x].size() == 1 && dp[x].front() == p)) {
        dp[x] = {1, 0};
        return;
    }
    int mx = INT_MIN, smx = INT_MIN;
    dp[x][1] = (int)g[x].size() - (p != -1);
    for (int u : g[x]) {
        if (u != p) {
            dfs(u, x);
            dp[x][1] = max(dp[x][1], dp[u][1] + ((int)g[x].size() - 1 - (p != -1)));
            dp[x][0] = max(dp[x][0], dp[u][1] + 1);
            dp[x][0] = max(dp[x][0], dp[u][0]);
            if (dp[u][1] > mx) {
                smx = mx;
                mx = dp[u][1];
            } else if (dp[u][1] > smx) {
                smx = dp[u][1];
            }
        }
    }
    dp[x][0] = max(dp[x][0], dp[x][1]);
    dp[x][0] = max(dp[x][0], mx + smx + ((int)g[x].size() - 2));
}

void solve() {
    int n;
    cin >> n;
    g.assign(n + 1, {});
    dp.assign(n + 1, {});
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1);
    // for (int i = 1; i <= n; ++i) {
    //     cout << i << ": " << dp[i][0] << ' ' << dp[i][1] << endl;
    // }
    cout << dp[1][0] << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}