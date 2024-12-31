#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) {
        char c;
        cin >> c;
        a[i] = c - '0';
    }
    for (int i = 1; i <= n; ++i) {
        char c;
        cin >> c;
        b[i] = c - '0';
    }
    vector<int> dp(n + 1);
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1];
        if (a[i] == 0 && b[i] == 1) {
            dp[i] = max(dp[i], dp[i - 1] + 1);
        }
        if (i - 2 >= 0 && a[i] + a[i - 1] == 2 && b[i] + b[i - 1] == 2) {
            dp[i] = max(dp[i], dp[i - 2] + 2);
        }
        if (i - 2 >= 0 && a[i] + a[i - 1] == 2 && b[i] + b[i - 1] == 1) {
            dp[i] = max(dp[i], dp[i - 2] + 1);
        }
    }
    int mx = 0;
    for (int i = 1; i <= n; ++i) {
        mx = max(mx, dp[i]);
    }
    cout << mx << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}