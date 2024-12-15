#include <bits/stdc++.h>
using namespace std;

int dp[101][10001];
array<int, 3> pr[101][10001];

void solve() {
    int n;
    cin >> n;
    dp[0][0] = 1;
    vector<int> a(n + 1);
    int s = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        s += a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        for (int cnt = n; cnt >= 0; --cnt) {
            for (int w = 10001 - a[i]; w >= 0; --w) {
                if (dp[cnt][w] && !dp[cnt + 1][w + a[i]]) {
                    dp[cnt + 1][w + a[i]] = dp[cnt][w];
                    pr[cnt + 1][w + a[i]] = {cnt, w, i};
                }
            }
        }
    }
    if ((n & 1) || (s & 1)) {
        cout << -1 << endl;
        return;
    }
    if (!dp[n / 2][s / 2]) {
        cout << -1 << endl;
        return;
    }
    pair<int, int> now = {n / 2, s / 2};
    vector<bool> seq(n + 1);
    while (now != pair<int, int>(0, 0)) {
        seq[pr[now.first][now.second][2]] = true;
        now = {pr[now.first][now.second][0], pr[now.first][now.second][1]};
    }
    for (int i = 1; i <= n; ++i) {
        if (seq[i]) cout << i << ' ';
    }
    cout << endl;
    for (int i = 1; i <= n; ++i) {
        if (!seq[i]) cout << i << ' ';
    }
    cout << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
