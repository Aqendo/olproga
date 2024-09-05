#pragma GCC target("popcnt")
#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> matr(n, vector(n, int(0)));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char t;
            cin >> t;
            matr[i][j] = t == 'Y';
        }
    }
    vector<vector<bool>> dp(1 << n, vector<bool>(n));
    for (int i = 0; i < n; ++i) {
        dp[1 << i][i] = true;
    }
    int mx_popcount = 0;
    for (int mask = 0; mask < 1 << n; ++mask) {
        if (!(__builtin_popcount(mask) & 1)) {
            for (int i = 0; i < n; ++i) {
                if (dp[mask][i]) {
                    for (int j = 0; j < n; ++j) {
                        if (!(mask >> j & 1)) {
                            dp[mask | (1 << j)][j] = true;
                        }
                    }
                    break;
                }
            }
            continue;
        }
        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) {
                if (dp[mask][i]) {
                    for (int j = 0; j < n; ++j) {
                        if (matr[i][j] && !(mask & (1 << j))) {
                            if (__builtin_popcount(mask | (1 << j)) >
                                mx_popcount) {
                                mx_popcount =
                                    __builtin_popcount(mask | (1 << j));
                            }
                            dp[mask | (1 << j)][j] = true;
                        }
                    }
                }
            }
        }
    }
    cout << mx_popcount << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
