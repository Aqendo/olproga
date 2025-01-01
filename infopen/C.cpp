#include <bits/stdc++.h>
using namespace std;
#define int int64_t
vector<vector<pair<int, bool>>> g;
int timer = 0;
vector<array<int, 2>> dp;
vector<int> used;
void dfs_stupid(int x, int parent = -1) {
    used[x] = timer;
    dp[x][1] = 1;
    dp[x][0] = 0;
    int most_weight = -1;
    for (auto [u, is_active] : g[x]) {
        if (!is_active) continue;
        if (used[u] != timer) {
            dfs_stupid(u, x);
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
int n;
vector<int> is_blocked;
void dfs_first_bin(int x, int parent = -1) {
    dp[x][1] = 1;
    dp[x][0] = 0;
    int most_weight = -1;
    for (int u : {x * 2, x * 2 + 1}) {
        if (u <= n) {
            dfs_first_bin(u, x);
            dp[x][1] += dp[u][0];
        }
    }
    dp[x][0] = dp[x][1] - 1;
    for (int u : {x * 2, x * 2 + 1}) {
        if (u <= n) {
            dp[x][0] = max(dp[x][0], dp[x][1] - dp[u][0] + dp[u][1] - 1);
        }
    }
}
void dfs_change(int x) {
    dp[x][1] = 1;
    dp[x][0] = 0;
    int most_weight = -1;
    for (int u : {x * 2, x * 2 + 1}) {
        if (u <= n && !is_blocked[u]) {
            dp[x][1] += dp[u][0];
        }
    }
    dp[x][0] = dp[x][1] - 1;
    for (int u : {x * 2, x * 2 + 1}) {
        if (u <= n && !is_blocked[u]) {
            dp[x][0] = max(dp[x][0], dp[x][1] - dp[u][0] + dp[u][1] - 1);
        }
    }
    if (!is_blocked[x] && x != 1) {
        dfs_change(x / 2);
    }
}
void stupid() {
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
            dfs_stupid(from);
            // for (int i = 1; i <= n; ++i) {
            //     cout << i << ": " << dp[i][0] << ' ' << dp[i][1] << endl;
            // }
            cout << dp[from][0] << '\n';
        }
    }
}

void binary() {
    cin >> n;
    vector<array<int, 4>> edges(n);
    g.assign(n + 1, {});
    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
    }
    int q;
    cin >> q;
    used.resize(n + 1);
    dp.resize(n + 1);
    is_blocked.resize(n + 1);
    dfs_first_bin(1);
    for (int i = 0; i < q; ++i) {
        int move;
        cin >> move;
        if (move == 1) {
            int road;
            cin >> road;
            is_blocked[road + 1] ^= 1;
            dfs_change((road + 1) >> 1);
        } else {
            int from;
            cin >> from;
            while (!is_blocked[from] && from != 1) {
                from /= 2;
            }
            cout << dp[from][0] << '\n';
        }
    }
}

void bamboo() {
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
    } else if (group == 4) {
        binary();
    }
}