#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 2e3 + 78;

int a[N], pref[N], dp[N][N];
int n, K;

void solve(int _l, int _r, int l, int r, int k) {
    if (l > r) return;
    int t = (l + r) >> 1;
    int opt = _l;
    for (int j = _l; j <= min(_r, t - 1); ++j) {
        int res = dp[j][k - 1] - (n - t + 1) * a[j] + (n - t + 1) * a[t];
        if (res < dp[t][k]) {
            opt = j;
            dp[t][k] = res;
        }
    }
    solve(_l, opt, l, t - 1, k);
    solve(opt, _r, t + 1, r, k);
}

int solve_me(int n_, int k_, const vector<int> &input) {
    cin >> n >> K;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= K; ++j) {
            dp[i][j] = 1e18;
        }
    }
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
    }
    sort(a + 1, a + n + 1, greater<int>());

    dp[1][1] = n * a[1] - pref[n];
    for (int k = 1; k <= K; ++k) {
        solve(1, n, 1, n, k);
    }
    int mn = 1e18;
    for (int i = 1; i <= n; ++i) {
        mn = min(mn, dp[i][K]);
    }
    return mn;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}
