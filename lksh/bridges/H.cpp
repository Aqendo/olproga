#include "bits/stdc++.h"

using namespace std;

constexpr int MAXN = 20002;
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);

multiset<pair<int, int>> g[MAXN];
int tin[MAXN];
bool used_a[MAXN];
int colors[MAXN];
int up[MAXN];
vector<int> s = {-1};

int color = 0;
int timer = 0;
set<int> answer;
map<pair<int, int>, int> cnt;

void dfs(int x, int p, int index) {
    s.push_back(x);
    bool ok = false;
    int c = 0;
    up[x] = tin[x] = timer++;
    used_a[x] = true;
    for (auto [u, index_] : g[x]) {
        if (u == p) continue;
        if (used_a[u]) {
            up[x] = min(up[x], tin[u]);
        } else {
            c++;
            dfs(u, x, index_);
            up[x] = min(up[x], up[u]);
            if (tin[x] <= up[u] && p != -1) {
                ok = true;
            }
        }
    }
    if (ok || (p == -1 && c > 1)) {
        answer.insert(x);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if (a == b) continue;
        g[a].emplace(b, i);
        g[b].emplace(a, i);
        cnt[{a, b}]++;
        cnt[{b, a}]++;
    }
    for (int i = 1; i <= n; ++i) {
        if (!used_a[i]) {
            dfs(i, -1, -1);
        }
    }
    cout << answer.size() << '\n';
    for (int i : answer) cout << i << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}