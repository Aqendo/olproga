#include "bits/stdc++.h"

using namespace std;
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

vector<vector<int>> g;
vector<vector<vector<int>>> dp;
const int INF = 1e9;

void dfs(int x, int p = -1) {
    for (int u : g[x]) {
        if (u != p) {
            dfs(u, x);
            if (g[u].size() == 1) {
                dp[x][0][0] = INF;
            } else {
                dp[x][0][0] += dp[u][0][1];
                dp[x][1][1] += min({dp[u][0][0], dp[u][0][1], dp[u][1][1]});
            }
        }
    }
    int mn = INT_MAX;
    int index = -1;
    for (int u : g[x]) {
        if (u != p) {
            if (mn > dp[u][1][1] - dp[u][0][1]) {
                mn = dp[u][1][1] - dp[u][0][1];
                index = u;
            }
        }
    }
    if (index == -1) {
        dp[x][0][1] = INF;
    } else {
        dp[x][0][1] = dp[index][1][1];
        for (int u : g[x]) {
            if (u != p && u != index) {
                dp[x][0][1] += min(dp[u][0][1], dp[u][1][1]);
            }
        }
    }
    dp[x][1][1]++;
    if (g[x].size() == 1 && x != 0) {
        dp[x][0][1] = INF;
    }
}

void solve() {
    int n;
    cin >> n;
    g.assign(n, {});
    dp.assign(n, vector(2, vector(2, 0)));
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }
    dfs(0);
    cout << min(dp[0][0][1], dp[0][1][1]) << '\n';
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
