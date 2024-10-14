#include "bits/stdc++.h"

using namespace std;

constexpr int MAXN = 20002;

unordered_multiset<int> g[MAXN];
int tin[MAXN];
bool used_a[MAXN];
int colors[MAXN];
int up[MAXN];
vector<int> s = {-1};
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);
int color = 0;
int timer = 0;

void dfs(int x, int p = -1) {
    s.push_back(x);
    up[x] = tin[x] = timer++;
    used_a[x] = true;
    for (int u : g[x]) {
        if (u == p) continue;
        if (used_a[u]) {
            up[x] = min(up[x], tin[u]);
        } else {
            dfs(u, x);
            up[x] = min(up[x], up[u]);
        }
    }

    if (tin[x] == up[x] && g[x].count(p) <= 1) {
        color++;
        int last = -1;
        while (last != x && !s.empty()) {
            colors[s.back()] = color;
            last = s.back();
            s.pop_back();
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if (a == b) continue;
        g[a].insert(b);
        g[b].insert(a);
    }
    for (int i = 1; i <= n; ++i) {
        if (!used_a[i]) {
            dfs(i, -1);
        }
    }
    cout << color << '\n';
    for (int i = 1; i <= n; ++i) {
        cout << colors[i] << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}