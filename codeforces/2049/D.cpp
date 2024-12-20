#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define int int64_t

int n, m, k;
int mod(int x) {
    return x >= m ? x - m : x;
}
int min(int a, int b) {
    return a < b ? a : b;
}
void solve() {
    cin >> n >> m >> k;
    vector dp(m, vector(n, vector(m, (int)1e18)));
    vector mn(m, vector(n, (int)1e18));

    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
    for (int j = 0; j < m; ++j) {
        dp[0][0][j] = a[0][j] + k * j;
        mn[0][0] = min(mn[0][0], dp[0][0][j]);
    }
    for (int i = 0; i < n; ++i) {
        for (int real_pos = 0; real_pos < m; ++real_pos) {
            for (int j = 0; j < m; ++j) {
                if (i > 0) {
                    dp[real_pos][i][j] = min(dp[real_pos][i][j], mn[real_pos][i - 1] + k * (mod(j - real_pos + m)) + a[i][j]);
                }
                if (real_pos > 0) {
                    dp[real_pos][i][j] = min(dp[real_pos][i][j], dp[real_pos - 1][i][mod(j - 1 + m)] + a[i][j]);
                }
                mn[real_pos][i] = min(mn[real_pos][i], dp[real_pos][i][j]);
            }
        }
    }
    cout << mn[m - 1][n - 1] << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}