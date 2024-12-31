#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<vector<int>> g;
vector<int> used;
vector<int> mt;
int timer = 0;
bool dfs(int v) {
    if (used[v] == timer)
        return false;
    used[v] = timer;
    for (int u : g[v]) {
        if (mt[u] == -1 || dfs(mt[u])) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}
void solve() {
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;
    g.assign(2 * n + 2, {});
    mt.assign(2 * n + 2, -1);
    for (int i = 0; i < n; ++i) {
        if (b[i] == '1') {
            if (i - 1 >= 0 && a[i - 1] == '1') {
                g[i].push_back(n + i - 1);
            }
            if (i + 1 < n && a[i + 1] == '1') {
                g[i].push_back(n + i + 1);
            }
            if (a[i] == '0') {
                g[i].push_back(n + i);
            }
        }
    }
    int cnt = 0;
    used.assign(2 * n + 2, {});
    for (int i = 0; i < n; i++) {
        timer++;
        if (dfs(i))
            cnt++;
    }
    for (int i = 0; i < n; ++i) {
        cout << mt[i + n] << '\n';
    }
    cout << cnt << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}