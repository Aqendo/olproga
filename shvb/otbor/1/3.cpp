#ifndef SEREGA
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define all(x) (x).begin(), (x).end()

void solve() {
    int n;
    cin >> n;
    vector<int8_t> can(24 * 60, true);
    for (int i = 0; i < n; ++i) {
        int from_hours, from_minutes, to_hours, to_minutes;
        string s;
        cin >> s;
        from_hours = (s[0] - '0') * 10 + s[1] - '0';
        from_minutes = (s[3] - '0') * 10 + s[4] - '0';
        to_hours = (s[6] - '0') * 10 + s[7] - '0';
        to_minutes = (s[9] - '0') * 10 + s[10] - '0';
        int from_time = from_hours * 60 + from_minutes;
        int to_time = to_hours * 60 + to_minutes - 1;
        for (int j = from_time; j <= to_time; ++j) {
            can[j] = false;
        }
    }
    can[19 * 60] = false;
    can[10 * 60 - 1] = false;
    int from_time = 10 * 60;
    int to_time = 19 * 60;
    int cooldown = 10;
    vector<int> dp(24 * 60);
    int mx = 0;
    for (int i = from_time; i <= to_time; ++i) {
        dp[i] = mx;
        if (!can[i]) continue;
        int already = 1;
        for (int j = i; j >= i - 20 + 1; --j) {
            if (!can[j]) break;
            dp[i] = max(dp[i], dp[j - cooldown - 1] + already);
            already++;
        }
        mx = max(mx, dp[i]);
    }
    // for (int i = from_time; i <= to_time; ++i) {
    //     cout << i / 60 << ":" << i % 60 << " - " << dp[i] << endl;
    // }
    cout << dp[to_time] << endl;
}

int32_t main() {
    solve();
}