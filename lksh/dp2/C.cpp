#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    if (n < m) swap(n, m);
    vector<vector<vector<int>>> dp(
        n + 1, vector<vector<int>>(m + 1, vector<int>((1 << (m + 1)))));
    for (int p = 0; p < (1 << (m + 1)); ++p) {
        dp[0][0][p]++;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int p = 0; p < (1 << (m + 1)); ++p) {
                for (int b = 0; b <= 1; ++b) {
                    int q = (p & ~(1 << (j + 1))) | (b << (j + 1));
                    int threeQ = (q >> j) & 7;
                    int threeP = (p >> j) & 7;
                    if (threeQ != threeP || (threeQ != 0 && threeQ != 7)) {
                        dp[i][j + 1][q] += dp[i][j][p];
                    }
                }
            }
        }
        for (int p = 0; p < (1 << (m + 1)); ++p) {
            dp[i + 1][0][(p & ~(1 << m)) << 1] += dp[i][m - 1][p];
            dp[i + 1][0][((p & ~(1 << m)) << 1) | 1] += dp[i][m - 1][p];
        }
    }
    int mx = INT_MIN;
    for (int p = 0; p < (1 << (m + 1)); ++p) {
        mx = max(mx, dp[n][0][p]);
    }
    cout << mx << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}