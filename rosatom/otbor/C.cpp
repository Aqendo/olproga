#include <bits/stdc++.h>
using namespace std;
#define int int64_t

bool can[4][4];
#define MAXN 100000 + 4
int dp[2][4];
const int MOD = 1e9 + 7;
int add(int x, int y) {
    return x + y >= MOD ? x + y - MOD : x + y;
}
void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int t;
            cin >> t;
            can[i][j] = t;
        }
    }
    dp[0][0] = 1;
    dp[0][1] = 1;
    dp[0][2] = 1;
    dp[0][3] = 1;
    int p = 0;
    for (int i = 2; i <= n; ++i) {
        p = 1 - p;
        for (int j = 0; j < 4; ++j) {
            dp[p][j] = 0;
        }
        for (int from = 0; from < 4; ++from) {
            for (int to = 0; to < 4; ++to) {
                if (can[from][to]) {
                    dp[p][to] = add(dp[p][to], dp[1 - p][from]);
                }
            }
        }
    }
    cout << add(dp[p][0], add(dp[p][1], add(dp[p][2], dp[p][3]))) << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}