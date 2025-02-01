#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<vector<pair<int, int>>> g;
clock_t ST;
double TL() {
    return (double)(clock() - ST) / CLOCKS_PER_SEC;
}
vector<int> vals;
vector<int> used;
int timer = 0;
void dfs(int x) {
    used[x] = true;
    for (auto [u, i] : g[x]) {
        if (!vals[i]) {
            vals[i] = ++timer;
        }
        if (!used[u]) {
            dfs(u);
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    g.assign(n, {});
    vals.assign(m, {});
    used.assign(n, {});

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }
    vector<int> indicies(n);
    iota(indicies.begin(), indicies.end(), 0);
    sort(indicies.begin(), indicies.end(), [](int a, int b) {
        return g[a].size() < g[b].size();
    });
    dfs(indicies[0]);
    bool good = true;
    for (int i = 0; i < n; ++i) {
        int already_gcd = 0;
        for (auto [u, j] : g[i]) {
            already_gcd = __gcd(already_gcd, vals[j]);
        }
        if (already_gcd != 1) {
            good = false;
            break;
        }
    }
    if (!good) {
        cout << -1 << '\n';
        return;
    }
    for (int i = 0; i < m; ++i) {
        cout << vals[i] << ' ';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}