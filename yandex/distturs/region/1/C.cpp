#pragma GCC optimize("O3")
#include "bits/stdc++.h"
using namespace std;
# ifdef SEREGA
# include "/home/ser/olproga/debug.h"
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
# endif

# ifndef SEREGA
# define printf(...)
# define debug(...)
# endif
const int MAX_SUM = 26 * 2501;
int dp[MAX_SUM + 1][2];
int pref[MAX_SUM + 1][2];
int po[2501];

const int MOD = 998'244'353;
int add(int x, int y) { return x + y >= MOD ? x + y - MOD : x + y; }
int sub(int x, int y) { return x - y < 0 ? x - y + MOD : x - y; }

void solve() {
    int n, m;
    cin >> n >> m;
    po[0] = 1;
    for (int i = 1; i < 2501; ++i) {
        po[i] = (po[i - 1] * 1ll * m) % MOD;
    }
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        char c; cin >> c;
        a[i] = c - 'a' + 1;
    }
    int answer = 0;
    int p = 0;
    dp[0][0] = 1;
    for (int i = 0; i <= MAX_SUM; ++i) {
        pref[i][0] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        p = 1 - p;
        dp[0][p] = 0;
        pref[0][p] = 0;
        for (int sum = 1; sum <= MAX_SUM; ++sum) {
            int from = sum - (m - a[i]);
            from = from >= 0 ? from : 0;
            int to = sum - 1;
            dp[sum][p] = sub(pref[to][1 - p], (from - 1 >= 0 ? pref[from - 1][1 - p] : 0));
            pref[sum][p] = add((sum - 1 >= 0 ? pref[sum - 1][p] : 0), dp[sum][p]);
            if (sum > 0 && sum % i == 0) {
                if (i != n) {
                    answer = add(answer, ((1ll * dp[sum][p] * a[i + 1]) % MOD) * po[n - i - 1] % MOD);
                } else {
                    answer = add(answer, dp[sum][p]);
                }
            }
        }
        // cout << "i = " << i << endl;
        // for (int j = 0; j < 30; ++j) {
        //     cout << dp[j][p] << ' ';
        // }
        // cout << endl;
        // for (int j = 0; j < 30; ++j) {
        //     cout << pref[j][p] << ' ';
        // }
        // cout << endl;
    }
    cout << answer << endl;
}

signed main() {
# ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
# endif
    solve();
}
