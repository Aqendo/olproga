#include <bits/stdc++.h>
using namespace std;
const int mod = 1001;
void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    vector<vector<int>> dp(1002, vector<int>(n + 1, 1e9));
    dp[0][0] = 0;
    for (int sum = 1; sum <= x; ++sum) {
        for (int already = 0; already <= n; ++already) {
            dp[sum % mod][already] = 1e9;
        }
        for (int already = 1; already <= n; ++already) {
            if (sum - a[already] >= 0) {
                dp[sum % mod][already] = min(dp[sum % mod][already], dp[(sum - a[already] % mod + mod) % mod][already - 1] + 1);
            }
        }
        if (sum - a[n] >= 0) {
            dp[sum % mod][n] = min(dp[sum % mod][n], dp[((sum - a[n]) % mod + mod) % mod][n] + 1);
        }
        for (int already = 1; already <= n; ++already) {
            dp[sum % mod][0] = min(dp[sum % mod][0], dp[sum % mod][already] + 1);
        }
    }
    int mn = 1e9;
    for (int already = 0; already <= n; ++already) {
        mn = min(mn, dp[x % mod][already]);
    }
    cout << (mn == 1e9 ? -1 : mn) << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
