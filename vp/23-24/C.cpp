#include <bits/stdc++.h>
using namespace std;
#define int int64_t

int a, b, p, q;
string s;
void solve() {
    cin >> a >> b >> p >> q >> s;
    if (s.size() == 1 && s[0] == '0') {
        cout << 0 << endl;
        return;
    }
    int n = s.size();
    vector<array<int, 2>> dp(n);
    assert(s[0] == '1');
    // 0 - +1, a/p
    // 1 - *2, b/q
    dp[0][0] = p + a;
    dp[0][1] = p + a + p + q;
    bool isInf = false;
    int num = 1;
    for (int i = 1; i < n; ++i) {
        if (num > 2 * int(INT_MAX)) {
            isInf = true;
            num = 2 * int(INT_MAX);
        }
        if (s[i] == '0') {
            cout << i << ": " << dp[i - 1][0] << endl;
            cout << i << ": " << dp[i - 1][0] + a * num << ' ' << dp[i - 1][1] + b + p + q << ' ' << dp[i - 1][1] + p + q + a * num << ' ' << dp[i - 1][0] + p + q + b + p + q << endl;
            dp[i][0] = min({dp[i - 1][0] + a * num, dp[i - 1][1] + b + p + q, dp[i - 1][1] + p + q + a * num, dp[i - 1][0] + p + q + b + p + q});
            dp[i][1] = min({dp[i - 1][1] + b, dp[i - 1][0] + p + q + b, dp[i - 1][0] + a * num + p + q, dp[i - 1][1] + p + q + a * num + p + q});
        } else {
            dp[i][0] = min({dp[i - 1][0] + a * (num + 1), dp[i - 1][1] + b + p + q + a, dp[i - 1][1] + p + q + a * (num + 1), dp[i - 1][0] + p + q + b + p + q + a});
            dp[i][1] = min({dp[i - 1][1] + b + p + q + a + p + q, dp[i - 1][0] + p + q + b + p + q + a + p + q, dp[i - 1][0] + a * (num + 1) + p + q, dp[i - 1][1] + p + q + a * (num + 1) + p + q});
        }

        if (!isInf)
            num = num * 2 + (s[i] == '1');
    }
    for (int i = 0; i < n; ++i) {
        cout << dp[i][0] << ' ' << dp[i][1] << endl;
    }
    cout << min(dp[n - 1][0] + p, dp[n - 1][1] + q) << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}