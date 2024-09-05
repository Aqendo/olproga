#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

vector<multiset<int>> g;
vector<int> order;

void dfs(int x) {
    while (!g[x].empty()) {
        int u = *g[x].begin();
        g[x].extract(u);
        g[u].extract(x);
        dfs(u);
    }
    order.push_back(x);
}

void solve() {
    int n;
    cin >> n;
    g.assign(n + 1, {});
    for (int u = 1; u <= n; ++u) {
        int m;
        cin >> m;
        for (int j = 0; j < m; ++j) {
            int v, length;
            cin >> v >> length;
            g[u].insert(v);
        }
    }
    vector<int> odd;
    for (int i = 1; i <= n; ++i) {
        if (g[i].size() & 1) {
            odd.push_back(i);
        }
    }
    if (odd.empty()) {
        dfs(1);
    } else if (odd.size() == 2) {
        dfs(odd.front());
    } else {
        cout << "-1\n";
        return;
    }
    cout << max<int>(0, (int)order.size() - 1) << '\n';
    for (int i : order) cout << i << ' ';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
