#include <bits/stdc++.h>
using namespace std;
#define int int64_t
namespace fast {

vector<vector<int>> g;
vector<int> dp, answer;

void countroot(int x, int p = -1) {
    int mx = 0;
    for (int u : g[x]) {
        if (u != p) {
            countroot(u, x);
            mx = max(mx, dp[u]);
        }
    }
    dp[x] = mx + 1;
}

void counteverything(int x, int p = -1, int mx_nad = 0) {
    cout << "HERE!" << endl;
    if (g[x].size() == 1) {
        if (p == -1) {
            answer[x] = dp[x] - 1;
            for (int u : g[x]) {
                if (u != p) {
                    cout << "now in " << x << " and getting into " << u << " with upper subtree of " << -1 << " and size of " << 1 << endl;
                    counteverything(u, x, 1);
                }
            }
            return;
        } else {
            answer[x] = mx_nad;
            return;
        }
    }
    if (g[x].empty()) return;
    auto get = [&](int vert) {
        return vert == p ? mx_nad : dp[vert];
    };
    int mx = g[x][0];
    int smx = g[x][1];
    if (get(mx) < get(smx)) swap(mx, smx);
    for (int i = 2; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (get(u) > get(mx)) {
            smx = mx;
            mx = u;
        } else if (get(u) > get(smx)) {
            smx = u;
        }
    }
    answer[x] = get(mx);
    for (int u : g[x]) {
        if (u != p) {
            if (u == mx) {
                cout << "now in " << x << " and getting into " << u << " with upper subtree of " << smx << " and size of " << get(smx) + 1 << endl;
                counteverything(u, x, get(smx) + 1);
            } else {
                cout << "now in " << x << " and getting into " << u << " with upper subtree of " << mx << " and size of " << get(mx) + 1 << endl;
                counteverything(u, x, get(mx) + 1);
            }
        }
    }
}

int solve(int n, int k, int c, const vector<pair<int, int>> &edges) {
    g.assign(n + 1, {});
    dp.assign(n + 1, {});
    answer.assign(n + 1, {});
    for (int i = 0; i < n - 1; ++i) {
        // int u, v;
        // cin >> u >> v;
        auto [u, v] = edges[i];
        g[u].push_back(v);
        g[v].push_back(u);
    }
    countroot(1);
    counteverything(1);
    vector<int> dist(n + 1, INT_MAX);
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int u : g[x]) {
            if (dist[x] + 1 < dist[u]) {
                q.push(u);
                dist[u] = dist[x] + 1;
            }
        }
    }
    int mx = 0;
    for (int i = 1; i <= n; ++i) {
        // cout << i << ": " << answer[i] << ' ' << dist[i] << endl;
        mx = max(mx, answer[i] * k - dist[i] * c);
    }
    return mx;
}
}  // namespace fast

namespace slow {
vector<vector<int>> g;
vector<int> dp, answer;

int dfs(int x, int p = -1) {
    int mx = 0;
    for (int u : g[x]) {
        if (u != p) {
            mx = max(mx, dfs(u, x));
        }
    }
    return mx + 1;
}

int solve(int n, int k, int c, const vector<pair<int, int>> &edges) {
    g.assign(n + 1, {});
    for (int i = 0; i < n - 1; ++i) {
        auto [u, v] = edges[i];
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> dist(n + 1, INT_MAX);
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int u : g[x]) {
            if (dist[x] + 1 < dist[u]) {
                q.push(u);
                dist[u] = dist[x] + 1;
            }
        }
    }
    int mx = 0;
    for (int i = 1; i <= n; ++i) {
        mx = max(mx, (dfs(i) - 1) * k - dist[i] * c);
    }
    return mx;
}
}  // namespace slow

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    //     mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    // #define uid(x, y) uniform_int_distribution<int>(x, y)(rng)
    //     while (true) {
    //         int n = uid(1, 10);
    //         int k = uid(1, 1000);
    //         int c = uid(1, 1000);
    //         vector<pair<int, int>> edges;
    //         edges.reserve(n - 1);
    //         for (int i = 2; i <= n; ++i) {
    //             edges.push_back({uid(1, i - 1), i});
    //         }
    //         if (fast::solve(n, k, c, edges) != slow::solve(n, k, c, edges)) {
    //             cout << n << ' ' << k << ' ' << c << endl;
    //             for (auto [u, v] : edges) {
    //                 cout << u << ' ' << v << endl;
    //             }
    //             cout << "ANSWERS: " << fast::solve(n, k, c, edges) << ' ' << slow::solve(n, k, c, edges) << endl;
    //             return 0;
    //         }
    //     }
    int t;
    cin >> t;
    while (t--) {
        int n, k, c;
        cin >> n >> k >> c;
        vector<pair<int, int>> edges(n - 1);
        for (int i = 0; i < n - 1; ++i) {
            cin >> edges[i].first >> edges[i].second;
        }
        cout << fast::solve(n, k, c, edges) << '\n';
    }
}