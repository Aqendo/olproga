#include <bits/stdc++.h>

using namespace std;

void solve() {
    int64_t n, m, u, v;
    cin >> n >> m;
    vector<int64_t> a(n + 3);
    cin >> a[1] >> u >> v;
    for (int64_t i = 2; i <= n; ++i) {
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
    }
    vector<vector<int64_t>> dp(__lg(n) + 1, vector<int64_t>(n + 1));
    dp[0] = a;
    for (int64_t power = 1; power <= __lg(n); power++) {
        for (int64_t i = 1; i <= n; ++i) {
            int64_t next_el = i + (1 << (power - 1));
            dp[power][i] = dp[power - 1][i];
            if (next_el <= n) {
                dp[power][i] = min(dp[power][i], dp[power - 1][next_el]);
            }
        }
    }
    vector<int64_t> lgg(n + 1);
    for (int64_t i = 0; i <= n; ++i) {
        lgg[i] = __lg(i);
    }
    int64_t ans = 0;
    for (int64_t q = 1; q <= m; ++q) {
        int64_t uu = u, vv = v;
        if (uu > vv) swap(uu, vv);
        int64_t len = lgg[vv - uu + 1];
        int64_t index_second = vv - (1 << len) + 1;
        ans = dp[len][uu];
        if (index_second <= n) {
            ans = min(ans, dp[len][index_second]);
        }
        if (q != m) {
            u = ((17 * u + 751 + ans + 2 * q) % n) + 1;
            v = ((13 * v + 593 + ans + 5 * q) % n) + 1;
        }
    }
    cout << u << ' ' << v << ' ' << ans << '\n';
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}