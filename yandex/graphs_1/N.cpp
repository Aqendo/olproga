#include "bits/stdc++.h"
using namespace std;

vector<vector<int>> g;
vector<int> mxp, dp;

void get_mxp(int x, int p = -1) {
    for (int u : g[x]) {
        if (u == p) continue;
        get_mxp(u, x);
        mxp[x] = max(mxp[x], mxp[u] + 1);
    }
}

void get_dp(int x, int p = -1) {
    int mx_1 = 0, mx_2 = 0;
    for (int u : g[x]) {
        if (u == p) continue;
        get_dp(u, x);
        if (mxp[u] > mx_1) {
            mx_2 = mx_1;
            mx_1 = mxp[u];
        } else if (mxp[u] > mx_2) {
            mx_2 = mxp[u];
        }
        dp[x] = max(dp[x], dp[u]);
    }
    dp[x] = max(dp[x], mx_1 + mx_2);
}

void solve() {
    int n;
    cin >> n;
    g.assign(n + 1, {});
    mxp.assign(n + 1, {});
    dp.assign(n + 1, {});
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
