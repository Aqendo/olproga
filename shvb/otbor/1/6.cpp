#include <bits/stdc++.h>
#define int int64_t
using namespace std;

vector<vector<int>> g;
vector<int> used;
int cnt = 0;

void dfs(int x) {
    used[x] = true;
    cnt++;
    for (int u : g[x]) {
        if (!used[u]) {
            dfs(u);
        }
    }
}
void solve() {
    int n, m;
    cin >> n >> m;
    g.assign(n + 1, {});
    used.assign(n + 1, {});
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int total_3 = 0, total_2 = 0, total_1 = 0;
    for (int i = 1; i <= n; ++i) {
        cnt = 0;
        if (!used[i]) {
            dfs(i);
        }
        int tri = cnt / 3;
        cnt -= cnt / 3 * 3;
        int dwa = cnt / 2;
        cnt -= cnt / 2 * 2;
        int odin = cnt;
        if (odin > 0) {
            if (tri > 0) {
                tri -= 1;
                dwa += 2;
                odin -= 1;
            }
        }
        total_3 += tri;
        total_2 += dwa;
        total_1 += odin;
    }
    cout << total_1 << endl;
    cout << total_2 << endl;
    cout << total_3 << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}