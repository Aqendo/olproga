#include <bits/stdc++.h>
using namespace std;
#define int int64_t
const int MAXN = 200002, MOD = 1e9 + 7;
int dp[MAXN][10][10];
int add(int x, int y) {
    return x + y >= MOD ? x + y - MOD : x + y;
}
void solve() {
    int n, m;
    cin >> n >> m;
    int answer = 0;
    while (n > 0) {
        int first = n % 10;
        for (int i = 0; i < 10; ++i) {
            answer = add(answer, dp[m][first][i]);
        }
        n /= 10;
    }
    cout << answer << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    for (int start = 0; start < 10; ++start) {
        dp[0][start][start] = 1;
    }
    for (int step = 1; step < MAXN; ++step) {
        for (int start = 0; start < 10; ++start) {
            for (int i = 0; i < 10; ++i) {
                dp[step][start][i] = dp[step - 1][start][(i + 9) % 10];
            }
            dp[step][start][1] = add(dp[step][start][1], dp[step - 1][start][9]);
        }
    }
    int t;
    cin >> t;
    while (t--) solve();
}