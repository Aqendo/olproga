#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

constexpr int MAXN = 200002;
constexpr int MOD = 1e9 + 7;

vector<int> g[MAXN];
int tin[MAXN];
bool used[MAXN];
int colors[MAXN];
long long colors_cnt[MAXN];
int up[MAXN];
vector<int> condensed_g[MAXN];
vector<int> s = {-1};

int color = 0;
int timer = 0;

void dfs(int x, int p = -1) {
    s.push_back(x);
    up[x] = tin[x] = timer++;
    used[x] = true;
    for (int u : g[x]) {
        if (u == p) continue;
        if (used[u]) {
            up[x] = min(up[x], tin[u]);
        } else {
            dfs(u, x);
            up[x] = min(up[x], up[u]);
        }
    }
    if (tin[x] == up[x]) {
        color++;
        int last = -1;
        while (last != x && !s.empty()) {
            colors_cnt[color]++;
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
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            dfs(i, -1);
        }
    }
    for (int x = 1; x <= n; ++x) {
        for (int u : g[x]) {
            if (colors[x] != colors[u]) {
                condensed_g[colors[x]].push_back(colors[u]);
            }
        }
    }
    long long ans = 1;
    vector<int> colors_res;
    for (int i = 1; i <= color; ++i) {
        if (condensed_g[i].size() <= 1) {
            colors_res.push_back(i);
        }
    }
    for (int i : colors_res) {
        ans = (ans * colors_cnt[i]) % MOD;
    }
    cout << colors_res.size() << ' ' << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}