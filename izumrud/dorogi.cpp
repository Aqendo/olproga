#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<vector<int>> g;
vector<int> used;
int answer = 0;
void dfs(int x) {
    if (x == 4) {
        answer++;
        return;
    }
    used[x] = true;
    for (int u : g[x]) {
        if (!used[u]) {
            dfs(u);
        }
    }
    used[x] = false;
}
void solve() {
    int n, m;
    cin >> n >> m;
    g.resize(n + 1);
    used.resize(n + 1);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1);
    cout << answer;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}