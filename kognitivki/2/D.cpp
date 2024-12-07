#include <bits/stdc++.h>
using namespace std;
const int MAXK = 100000 + 42;
int dp[MAXK];

void solve() {
    fill(dp, dp + MAXK, 1e9 + 1);
    dp[0] = 0;
    for (int i = 0; i < MAXK; ++i) {
        for (int cycle = 3; cycle < 448; ++cycle) {
            int toadd = cycle * (cycle - 1) / 2;
            if (i + toadd >= MAXK) break;
            if (dp[i] == 0) {
                dp[i + toadd] = min(dp[i + toadd], dp[i] + cycle);
            } else {
                dp[i + toadd] = min(dp[i + toadd], dp[i] + cycle - 1);
            }
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int n, k;
        cin >> n >> k;
        cout << (dp[k] <= n ? "YES\n" : "NO\n");
    }
}
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}