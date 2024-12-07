#include <bits/stdc++.h>
#define int int64_t
using namespace std;

void solve() {
    int n, d;
    cin >> n >> d;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    vector<int> dp(n + 1, INT_MIN);
    dp[0] = 0;
    auto getdp = [&dp](int index) { return (index >= 0 ? dp[index] : INT_MIN); };
    auto geta = [&a](int index) { return (index >= 0 ? a[index] : INT_MIN); };
    for (int i = 1; i <= n; ++i) {
        dp[i] = max(getdp(i - 2), getdp(i - 1));
        if (geta(i) - geta(i - 1) <= d) {
            dp[i] = max(dp[i], getdp(i - 2) + 1);
        }
    }
    cout << dp[n] << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
