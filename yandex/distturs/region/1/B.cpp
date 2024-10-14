#ifndef SEREGA
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define int int64_t
using namespace std;
#ifdef SEREGA
#include "/home/ser/olproga/debug.h"
auto __freop = freopen(INPUT_PATH, "r", stdin);
#else
#define debug(...)
#endif

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()


void solve() {
	int n, m; cin >> n >> m;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	vector<vector<int>> dp(n + 1, vector<int> (10001, (int)1e18));
	dp[0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int bi = a[i]; bi >= 1; --bi) {
			for (int now = )
		}
	}
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}
