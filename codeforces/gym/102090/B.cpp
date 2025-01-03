#include <bits/stdc++.h>
using namespace std;
#define int int64_t
const int MOD = 1e9 + 7;
int add(int x, int y) { return x + y >= MOD ? x + y - MOD : x + y; }
int sub(int x, int y) { return x - y < 0 ? x - y + MOD : x - y; }
void solve() {
    int n, k;
    cin >> n >> k;
    vector dp(2, vector(n + 1, vector(n + 1, 0)));
    vector pref(2, vector(n + 1, vector(n + 1, 0)));

    dp[0][k][k] = 1;
    for (int i = k; i <= n; ++i) {
        pref[0][k][i] = 1;
        pref[1][k][i] = 1;
    }
    dp[1][k][k] = 1;
    // o - previous is bigger
    // 1 - previous is smaller
    for (int newS = k; newS <= n; ++newS) {
        for (int newEl = 1; newEl <= newS; ++newEl) {
            if (min(newS - newEl, newEl - 1) >= 0) {
                dp[1][newS][newEl] = add(dp[1][newS][newEl], pref[0][newS - newEl][min(newS - newEl, newEl - 1)]);
            }
            if (newEl + 1 <= newS - newEl) {
                dp[0][newS][newEl] = add(dp[0][newS][newEl], sub(pref[1][newS - newEl][newS - newEl], pref[1][newS - newEl][newEl]));
            }
            pref[0][newS][newEl] = add(pref[0][newS][newEl - 1], dp[0][newS][newEl]);
            pref[1][newS][newEl] = add(pref[1][newS][newEl - 1], dp[1][newS][newEl]);
            // for (int lastEl = 1; lastEl <= min(newS - newEl, newEl - 1); ++lastEl) {
            //     dp[1][newS][newEl] = add(dp[1][newS][newEl], dp[0][newS - newEl][lastEl]);
            // }
            // for (int lastEl = newEl + 1; lastEl <= newS - newEl; ++lastEl) {
            //     dp[0][newS][newEl] = add(dp[0][newS][newEl], dp[1][newS - newEl][lastEl]);
            // }
        }
    }
    int answer = add(pref[0][n][n], pref[1][n][n]);
    // for (int el = 1; el <= n; ++el) {
    //     answer = add(answer, dp[0][n][el]);
    //     answer = add(answer, dp[1][n][el]);
    // }
    if (k == n) answer = (answer - 1 + MOD) % MOD;
    cout << answer << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}