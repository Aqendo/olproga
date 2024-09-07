#include "bits/stdc++.h"

using namespace std;
#define int long long
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif
struct Node {
    int a, index;
};
string to_string(const Node& n) {
    return "(a=" + to_string(n.a) + ";i=" + to_string(n.index) + ")";
}
int n;
vector<Node> a;

void solve() {
    cin >> n;
    a.assign(n + 1, {});
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].a;
        a[i].index = i;
    }
    sort(a.begin() + 1, a.end(), [](auto& p1, auto& p2) { return p1.a > p2.a; });
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    int mx = 0;
    for (int i = 1; i <= n; ++i) {
        for (int len = 0; len < i; ++len) {
            // debug(i, len);
            // cout << format("1index {} to {} is {}\n", a[i].index, len + 1, a[i].a * abs(a[i].index - len - 1));
            // cout << format("2index {} to {} is {}\n", a[i].index, n - i + len + 1, a[i].a * abs(a[i].index - (n - i + len + 1)));

            dp[len + 1][i] = max(dp[len + 1][i], dp[len][i - 1] + a[i].a * abs(a[i].index - len - 1));
            dp[len][i] = max(dp[len][i], dp[len][i - 1] + a[i].a * abs(a[i].index - (n - i + len + 1)));
            // debug(dp[len + 1][i], dp[len][i]);
            mx = max({mx, dp[len + 1][i], dp[len][i]});
        }
    }
    cout << mx;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
