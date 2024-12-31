#include <bits/stdc++.h>
using namespace std;
clock_t ST;
double TL() {
    return (double)(clock() - ST) / CLOCKS_PER_SEC;
}
int ans = INT_MAX;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }
    sort(a.begin(), a.end());
    vector<int> result(n);
    int timer = 0;
    for (int i = 1; i < n; i += 2) {
        result[i] = a[timer++];
    }
    for (int i = 0; i < n; i += 2) {
        result[i] = a[timer++];
    }
    int cnt = 0;
    vector<array<int, 2>> dp(n);
    dp[0] = {0, 1};
    for (int i = 1; i < n; ++i) {
        if (i & 1) {
            if (result[i - 1] > result[i]) {
                dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]);
                dp[i][1] = dp[i][0] + 1;
            } else {
                dp[i][0] = dp[i - 1][1];
                dp[i][1] = min({dp[i - 1][0], dp[i - 1][1]}) + 1;
            }
        } else {
            if (result[i - 1] < result[i]) {
                dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]);
                dp[i][1] = dp[i][0] + 1;
            } else {
                dp[i][0] = dp[i - 1][1];
                dp[i][1] = min({dp[i - 1][0], dp[i - 1][1]}) + 1;
            }
        }
    }
    cout << min(dp[n - 1][0], dp[n - 1][1]) << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}