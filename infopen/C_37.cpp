#include <bits/stdc++.h>
using namespace std;
#define int int64_t
vector<vector<pair<int, bool>>> g;
int timer = 0;
vector<array<int, 2>> dp;
vector<int> used;
void dfs(int x, int parent = -1) {
    used[x] = timer;
    dp[x][1] = 1;
    dp[x][0] = 0;
    int most_weight = -1;
    for (auto [u, is_active] : g[x]) {
        if (!is_active) continue;
        if (used[u] != timer) {
            dfs(u, x);
            dp[x][1] += dp[u][0];
        }
    }
    dp[x][0] = dp[x][1] - 1;
    for (auto [u, is_active] : g[x]) {
        if (!is_active) continue;
        if (u != parent) {
            dp[x][0] = max(dp[x][0], dp[x][1] - dp[u][0] + dp[u][1] - 1);
        }
    }
}
void stupid() {
    int n;
    cin >> n;
    vector<array<int, 4>> edges(n);
    g.assign(n + 1, {});
    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        edges[i] = {a, b, 0, 0};
        g[a].push_back({b, true});
        edges[i][2] = g[a].size() - 1;
        g[b].push_back({a, true});
        edges[i][3] = g[b].size() - 1;
    }
    int q;
    cin >> q;
    used.resize(n + 1);
    dp.resize(n + 1);
    for (int i = 0; i < q; ++i) {
        int move;
        cin >> move;
        if (move == 1) {
            int road;
            cin >> road;
            g[edges[road][0]][edges[road][2]].second ^= 1;
            g[edges[road][1]][edges[road][3]].second ^= 1;
        } else {
            int from;
            cin >> from;
            timer++;
            dfs(from);
            // for (int i = 1; i <= n; ++i) {
            //     cout << i << ": " << dp[i][0] << ' ' << dp[i][1] << endl;
            // }
            cout << dp[from][0] << '\n';
        }
    }
}

void bamboo() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
    }
    set<int> blocked;
    blocked.insert(0);
    blocked.insert(n);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int move, x;
        cin >> move >> x;
        if (move == 1) {
            if (blocked.contains(x)) {
                blocked.erase(x);
            } else {
                blocked.insert(x);
            }
        } else {
            auto it = blocked.lower_bound(x);
            auto pre = prev(it);
            int from = *pre + 1, to = *it - 1;
            int cnt = to - from + 1;
            cout << (cnt + 1) / 2 << '\n';
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int group;
    cin >> group;
    if (group == 2) {
        bamboo();
    } else if (group == 0 || group == 1 || group == 3) {
        stupid();
    }
}