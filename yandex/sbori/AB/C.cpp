#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 1e5 + 1;

vector<int> g[N];
int used[N], col[N];

void dfs(int x, int p) {
    used[x] = 1;
    col[x] = p;
    for (int u : g[x]) {
        if (!used[u]) {
            dfs(u, 1 - p);
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
            dfs(i, 0);
        }
    }
    for (int x = 1; x <= n; ++x) {
        int now = col[x];
        bool good = false;
        for (int u : g[x]) {
            if (col[u] != now) {
                good = true;
                break;
            }
        }
        if (!good) {
            cout << -1 << '\n';
            return;
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << col[i] + 1 << ' ';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    while (t--) solve();
}