#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

vector<vector<int>> g;
vector<bool> used_a;
vector<int> tin, fup;
vector<int> answer;
int n, m;
int timer = 0;

void dfs(int x, int p = -1) {
    bool ok = false;
    used_a[x] = true;
    fup[x] = tin[x] = timer++;
    int c = 0;
    for (int u : g[x]) {
        if (u == p) continue;
        if (!used_a[u]) {
            dfs(u, x);
            fup[x] = min(fup[x], fup[u]);
            if (tin[x] <= fup[u] && p != -1) {
                ok = true;
            }
            c++;
        } else {
            fup[x] = min(fup[x], tin[u]);
        }
    }
    if (ok || (p == -1 && c > 1)) {
        if (x < m) {
            answer.push_back(x);
        }
    }
}

void init() {
    g.assign(n + m + 2, {});
    used_a.assign(n + m + 2, {});
    tin.assign(n + m + 2, {});
    fup.assign(n + m + 2, {});
}

void solve() {
    cin >> n >> m;
    init();
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[i].push_back(a + m);
        g[a + m].push_back(i);
        g[i].push_back(b + m);
        g[b + m].push_back(i);
        g[i].push_back(c + m);
        g[c + m].push_back(i);
    }
    for (int i = 0; i < n + m + 2; ++i) {
        if (!used_a[i]) {
            dfs(i);
        }
    }
    cout << answer.size() << '\n';
    sort(answer.begin(), answer.end());
    for (int i = 0; i < answer.size(); ++i) {
        cout << answer[i] + 1 << ' ';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}