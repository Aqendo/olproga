#include <bits/stdc++.h>
using namespace std;

vector<multiset<int>> g;
vector<int> result;
void dfs(int x) {
    while (!g[x].empty()) {
        int v = *g[x].rbegin();
        g[x].extract(*g[x].rbegin());
        g[v].extract(x);
        dfs(v);
    }
    result.push_back(x);
}

void solve() {
    int n;
    cin >> n;
    g.assign(n + 1, {});
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        int t;
        cin >> t;
        cnt += t;
        for (int j = 0; j < t; ++j) {
            int b;
            cin >> b;
            g[i].insert(b);
        }
    }
    int vertex = 1;
    for (int i = 1; i <= n; ++i) {
        if ((int)g[i].size() & 1) {
            vertex = i;
            break;
        }
    }
    dfs(vertex);
    if (cnt / 2 != (int)result.size() - 1) {
        cout << -1 << endl;
        return;
    }
    cout << (int)result.size() - 1 << endl;
    for (int i = (int)result.size() - 1; i >= 0; --i) {
        cout << result[i] << ' ';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
