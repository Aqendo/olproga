#include <bits/stdc++.h>
using namespace std;
#define int int64_t

#define MAXN 300'042

vector<vector<int>> g;
vector<vector<int>> cycles;
vector<int> st_;

int8_t used[MAXN];
bool is_on_cycle[MAXN];
int dp[MAXN][2];

void get_cycles(int x, int parent = -1) {
    used[x] = 1;
    st_.push_back(x);
    for (int u : g[x]) {
        if (!used[u]) {
            get_cycles(u, x);
        }
        if (used[u] == 1 && u != parent) {
            cycles.push_back({});
            for (int i = ssize(st_) - 1; i >= 0; --i) {
                is_on_cycle[st_[i]] = true;
                cycles.back().push_back(st_[i]);
                if (st_[i] == u) break;
            }
        }
    }
    st_.pop_back();
    used[x] = 2;
}

void count_dp(int x) {
    used[x] = true;
    dp[x][1] = 1;
    for (int u : g[x]) {
        if (!used[u] && !is_on_cycle[u]) {
            count_dp(u);
            dp[x][1] += dp[u][0];
            dp[x][0] += max(dp[u][0], dp[u][1]);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    g.assign(n, {});
    for (int i = 0; i < n; ++i) {
        int ai;
        cin >> ai;
        if (ai != -1) {
            ai--;
            g[i].push_back(ai);
            g[ai].push_back(i);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            get_cycles(i);
        }
    }
    fill(used, used + MAXN, 0);
    for (auto &cycle : cycles) {
        for (int vert : cycle) {
            count_dp(vert);
        }
    }
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            count_dp(i);
            answer += max(dp[i][0], dp[i][1]);
        }
    }
    for (auto &cycle : cycles) {
        // cout << "in cycle: ";
        // for (int i : cycle) cout << i << ' ';
        // cout << endl;
        int temp_answer = 0;
        vector<array<int, 2>> ndp(cycle.size(), {0, 0});
        ndp[0][1] = max(dp[cycle[0]][1], dp[cycle[0]][0]);
        ndp[0][0] = dp[cycle[0]][0];

        for (int i = 1; i < ssize(cycle); ++i) {
            ndp[i][0] = max(ndp[i - 1][0], ndp[i - 1][1]) + dp[cycle[i]][0];
            ndp[i][1] = ndp[i - 1][0] + max(dp[cycle[i]][0], dp[cycle[i]][1]);
        }
        // for (int i = 0; i < ssize(cycle); ++i) {
        //     cout << cycle[i] << ": " << ndp[i][0] << " " << ndp[i][1] << endl;
        // }
        temp_answer = ndp[ssize(cycle) - 1][0];
        ndp.assign(cycle.size(), {0, 0});
        ndp[0][0] = dp[cycle[0]][0];
        for (int i = 1; i < ssize(cycle); ++i) {
            ndp[i][0] = max(ndp[i - 1][0], ndp[i - 1][1]) + dp[cycle[i]][0];
            ndp[i][1] = ndp[i - 1][0] + max(dp[cycle[i]][0], dp[cycle[i]][1]);
        }
        // for (int i = 0; i < ssize(cycle); ++i) {
        //     cout << cycle[i] << ": " << ndp[i][0] << " " << ndp[i][1] << endl;
        // }
        temp_answer = max({temp_answer, ndp[ssize(cycle) - 1][0], ndp[ssize(cycle) - 1][1]});
        answer += temp_answer;
    }
    cout << answer << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}