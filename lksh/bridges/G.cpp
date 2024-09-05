#include "bits/stdc++.h"

using namespace std;

constexpr int MAXN = 20002;

vector<pair<int, int>> g[MAXN];
int tin[MAXN];
bool used_a[MAXN];
int colors[MAXN];
int up[MAXN];
vector<int> s = {-1};

int color = 0;
int timer = 0;
set<int> answer;

void dfs(int x, int p, int index) {
    s.push_back(x);
    up[x] = tin[x] = timer++;
    used_a[x] = true;
    int cnt_p = 0;
    for (auto [u, index_] : g[x]) {
        if (u == p) {
            cnt_p++;
            continue;
        }
        if (used_a[u]) {
            up[x] = min(up[x], tin[u]);
        } else {
            dfs(u, x, index_);
            up[x] = min(up[x], up[u]);
        }
    }

    if (tin[x] == up[x] && cnt_p <= 1) {
        if (p != -1) answer.insert(index + 1);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if (a == b) continue;
        g[a].emplace_back(b, i);
        g[b].emplace_back(a, i);
    }
    for (int i = 1; i <= n; ++i) {
        if (!used_a[i]) {
            dfs(i, -1, -1);
        }
    }
    cout << answer.size() << '\n';
    for (int i : answer) cout << i << ' ';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}