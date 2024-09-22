#include "bits/stdc++.h"
using namespace std;
#define int long long
#define double long double
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

#ifndef SEREGA
#define printf(...)
#define debug(...)
#endif

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, int> ind;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        ind[a[i]] = i;
    }
    for (int offset = 0; offset < n; ++offset) {
        int ans([&]() {
            vector<vector<int>> dp(1 << (n - offset), vector<int>(n, LLONG_MAX));
            for (int j = offset; j < n; ++j) {
                dp[1 << j][j] = 0;
            }
            for (int mask = 0; mask < (1 << (n - offset)); ++mask) {
                for (int j = offset; j < n; ++j) {
                    if (dp[mask][j]) {
                        if () }
                }
            }
        })();
    }
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
