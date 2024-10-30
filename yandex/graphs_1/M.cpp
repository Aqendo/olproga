#pragma GCC optimize("O3")
#include "bits/stdc++.h"
%:define int int64_t
using namespace std;

struct Node {
    long long sum;
    int cnt;
    bool operator<(const Node& r) const {
        if (sum != r.sum) return sum < r.sum;
        return cnt < r.cnt;
    }
    Node operator+(const Node& r) { return {sum + r.sum, cnt + r.cnt}; }
};
Node min(const Node& l, const Node& r) {
    return l < r ? l : r;
}
vector<vector<int>> g;
vector<vector<Node>> dp;
vector<int> cost;
map<pair<int, int>, int> pre;
// 1 - not lighten not covered
// 2 - not lighten covered
// 3 - lighten

void dfs(int x, int p = -1) {
    if ((g[x].size() <= 1 && p != -1) || (g[x].empty() && p == -1)) {
        dp[x][0] = {0, 0};
        dp[x][1] = {cost[x], 1};
        return;
    }
    for (int u : g[x]) {
        if (u != p) {
            dfs(u, x);
            // printf("%d: 0=[%lld,%d], 1=[%lld,%d]\n", u, dp[u][0].sum, dp[u][0].cnt, dp[u][1].sum, dp[u][1].cnt);
            dp[x][0] = dp[x][0] + dp[u][1];
            dp[x][1] = dp[x][1] + min(dp[u][1], dp[u][0]);
            pre[{x, u}] = dp[u][1] < dp[u][0] ? 1 : 0;
        }
    }
    dp[x][1] = dp[x][1] + Node{cost[x], 1};
}

vector<int> answer;

void get_answer(int x, int type, int p = -1) {
    if (type == 1) answer.push_back(x);
    for (int u : g[x]) {
        if (u != p) {
            if (type == 0) {
                get_answer(u, 1, x);
            } else {
                // assert(pre.find({x, u}) != pre.end());
                get_answer(u, pre[{x, u}], x);
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;
    g.assign(n + 1, {});
    cost.assign(n + 1, {});
    dp.assign(n + 1, vector<Node>(2));
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> cost[i];
    }
    dfs(1);
    pair<int, int> now = dp[1][0] < dp[1][1] && !g[1].empty() ? pair{1, 0} : pair{1, 1};
    cout << dp[now.first][now.second].sum << ' ' << dp[now.first][now.second].cnt << endl;
    get_answer(now.first, now.second);
    for (int i : answer) {
        cout << i << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
