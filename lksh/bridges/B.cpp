#include "bits/stdc++.h"
using namespace std;

constexpr int MAXN = 20002;

multiset<pair<int, int>> g[MAXN];
int tin[MAXN];
bool used_a[MAXN];
int up[MAXN];
vector<pair<int, int>> s = {{-1, -1}};
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);

int color = 0;
int timer = 0;
map<pair<int, int>, int> colors;

void dfs(int x, int p) {
    up[x] = tin[x] = timer++;
    used_a[x] = true;
    for (auto [u, index_] : g[x]) {
        if (u == p) continue;
        if (used_a[u]) {
            up[x] = min(up[x], tin[u]);
            if (tin[u] < tin[x]) {
                s.emplace_back(x, u);
            }
        } else {
            s.emplace_back(x, u);
            dfs(u, x);
            up[x] = min(up[x], up[u]);
            if (tin[x] <= up[u]) {
                color++;
                int xx = s.back().first, uu = s.back().second;
                while ((xx != x && xx != u) || (uu != x && uu != u)) {
                    colors[{xx, uu}] = color;
                    colors[{uu, xx}] = color;
                    s.pop_back();
                    xx = s.back().first, uu = s.back().second;
                }
                colors[{xx, uu}] = color;
                colors[{uu, xx}] = color;
                s.pop_back();
            }
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        edges[i] = {a, b};
        if (a == b) continue;
        g[a].emplace(b, i);
        g[b].emplace(a, i);
    }
    for (int i = 1; i <= n; ++i) {
        if (!used_a[i]) {
            dfs(i, -1);
        }
    }
    vector<int> min_edge_by_colors(colors.size() + 1, INT_MAX);
    for (int i = 0; i < m; ++i) {
        min_edge_by_colors[colors[edges[i]]] = min(min_edge_by_colors[colors[edges[i]]], i);
    }
    vector<int> color_per(colors.size() + 1);
    cout << color << '\n';
    timer = 1;
    for (int i = 0; i < m; ++i) {
        if (color_per[colors[edges[i]]] == 0) {
            color_per[colors[edges[i]]] = timer++;
        }
        cout << color_per[colors[edges[i]]] << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}