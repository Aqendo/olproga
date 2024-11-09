#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve(int n) {
    vector<vector<int>> dp(n + 1, vector<int>(n, LLONG_MIN));
    vector parent(n + 1, vector(n, pair<int, int>(-1, -1)));

    dp[1][1] = 1;
    for (int i = 1; i <= n - 1; ++i) {
        for (int prev = 1; prev <= n - 1; ++prev) {
            for (int from = i - 1; from >= 1; --from) {
                if (dp[from][prev] + 1 > dp[i][(prev * i) % n]) {
                    dp[i][(prev * i) % n] = dp[from][prev] + 1;
                    parent[i][(prev * i) % n] = {from, prev};
                }
            }
        }
    }
    int mx = n - 1;
    for (int i = 1; i <= n - 1; ++i) {
        if (dp[i][1] > dp[mx][1]) mx = i;
    }
    cout << dp[mx][1] << endl;
    vector<int> nums;
    pair<int, int> now = {mx, 1};
    while (now != pair<int, int>{-1, -1}) {
        nums.push_back(now.first);
        now = parent[now.first][now.second];
    }
    for (int i = (int)nums.size() - 1; i >= 0; --i) {
        cout << nums[i] << ' ';
    }
}

void solve() {
    for (int i = 2; i < 20; ++i) {
        cout << i << "===================\n";
        solve(i);
        cout << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}