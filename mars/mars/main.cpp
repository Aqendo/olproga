#include <bits/stdc++.h>
#define int int64_t
using namespace std;
#ifdef SEREGA
#include "/home/ser/olproga/debug.h"
auto __freop = freopen("/home/ser/olproga/input.txt", "r", stdin);
#else
#define debug(...)
#endif

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

int n, m;
vector<int> a;

int solve_slow() {
    vector<vector<int>> dp(n + 1, vector<int> (m + 1, LLONG_MAX));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int bi = a[i]; bi >= 1; --bi) {
            for (int now = 0; now + bi * bi <= m; ++now) {
                if (dp[i - 1][now] != LLONG_MAX) {
                    dp[i][now + bi * bi] = min(dp[i][now + bi * bi], dp[i - 1][now] + (a[i] - bi) * (a[i] - bi));
                }
            }
        }
    }
    return (dp[n][m] == LLONG_MAX ? -1 : dp[n][m]);
}

int solve_norm() {
	vector<map<int, int>> dp(n + 1);
	dp[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int bi = a[i]; bi >= 1; --bi) {
			for (auto [j, _] : dp[i - 1]) {
		if (j + bi * bi > m + 3) break;
                if (dp[i].find(j + bi * bi) == dp[i].end()) {
                    dp[i][j + bi * bi] = dp[i - 1][j] + (a[i] - bi) * (a[i] - bi);
                } else {
                    dp[i][j + bi * bi] = min(dp[i][j + bi * bi], dp[i - 1][j] + (a[i] - bi) * (a[i] - bi));
                }
			}
		}
	}
	return (dp[n].find(m) != dp[n].end() ? dp[n][m] : -1);
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
/*
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    #define uid(x, y) uniform_int_distribution(x, y)(rng)
    int tc = 0;
    while (true) {
        cout << "test: " << tc++ << endl;
        n = uid(1, 5);
        m = uid(1, 10000);
        a.assign(n + 1, {});
        for (int i = 1; i <= n; ++i) {
            a[i] = uid(1, 100);
        }
        int norm = solve_norm();
        int slow = solve_slow();
        if (norm != slow) {
            cout << n << ' ' << m << endl;
            for (int i : a) cout << i << ' ';
            cout << endl;
            cout << "norm output: " << norm << endl;
            cout << "slow output: " << slow << endl;
            exit(0);
        }
    }*/
	cin >> n >> m;
	a.assign(n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
    cout << solve_norm();
    // cout << solve_norm();
}
