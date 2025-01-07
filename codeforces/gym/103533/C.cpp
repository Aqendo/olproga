#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<vector<pair<int, int>>> g;
vector<array<pair<int, int>, 2>> dp;
int n, k;
void dfs(int x) {
    pair<int, int> dpsum = {0, 0};
    for (auto [u, w] : g[x]) {
        dfs(u);
        dpsum.first += dp[u][0].first;
        dpsum.second += dp[u][0].second;
    }
    sort(g[x].begin(), g[x].end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        pair<int, int> f = {dp[a.first][0].first + 1 - dp[a.first][1].first, -(dp[a.first][0].second + a.second - dp[a.first][1].second)};
        pair<int, int> s = {dp[b.first][0].first + 1 - dp[b.first][1].first, -(dp[b.first][0].second + b.second - dp[b.first][1].second)};
        return f > s;
    });
    int remain = k;
    for (int i = 0; i < (int)g[x].size(); ++i) {
        pair<int, int> zero = dp[g[x][i].first][0];
        pair<int, int> one = dp[g[x][i].first][1];
        pair<int, int> zero_result = {zero.first + 1, -(zero.second + g[x][i].second)};
        pair<int, int> one_result = {one.first, -(one.second)};
        // cout << "in " << x << "; zero_result = " << zero_result.first << ' ' << zero_result.second << "; one_result = " << one_result.first << ' ' << one_result.second << endl;
        if (one_result > zero_result) {
            // cout << "one_result chosen\n";
            dp[x][1].first += one_result.first;
            dp[x][1].second += -one_result.second;
            dp[x][0].first += one_result.first;
            dp[x][0].second += -one_result.second;
        } else {
            if (remain > 1) {
                // cout << "zero_result 1 chosen\n";
                dp[x][1].first += zero_result.first;
                dp[x][1].second += -zero_result.second;
                dp[x][0].first += zero_result.first;
                dp[x][0].second += -zero_result.second;
                remain--;
            } else if (remain == 1) {
                // cout << "zero_result 2 chosen\n";
                dp[x][1].first += zero_result.first;
                dp[x][1].second += -zero_result.second;
                dp[x][0].first += one_result.first;
                dp[x][0].second += -one_result.second;
                remain--;
            } else {
                // cout << "zero_result 3 chosen\n";
                dp[x][1].first += one_result.first;
                dp[x][1].second += -one_result.second;
                dp[x][0].first += one_result.first;
                dp[x][0].second += -one_result.second;
            }
        }
    }
}

void solve() {
    cin >> n >> k;
    g.assign(n + 1, {});
    dp.assign(n + 1, {});
    for (int i = 0; i < n - 1; ++i) {
        int p, w;
        cin >> p >> w;
        g[p].emplace_back(i + 2, w);
    }
    dfs(1);
    cout << dp[1][1].first << ' ' << dp[1][1].second << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}