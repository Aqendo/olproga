#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> grid1(n, vector<int>(n));
    vector<vector<int>> grid2 = grid1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> grid1[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid2[i][j];
        }
    }

    for (int newi = 0; newi < n; ++newi) {
        for (int newj = 0; newj < n; ++newj) {
            vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
            dp[0][0] = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (i == 0 && j == 0) continue;
                }
            }
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}