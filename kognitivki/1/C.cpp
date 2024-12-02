#include "bits/stdc++.h"
using namespace std;
#define int int64_t
vector<vector<int>> g;

pair<int, int> get_diameter(int x, int p = -1) {
    int sz = 0;
    int vertex = x;
    for (int u : g[x]) {
        if (u == p) continue;
        pair<int, int> ans = get_diameter(u, x);
        if (ans.second > sz) {
            sz = ans.second;
            vertex = ans.first;
        }
    }
    sz += 1;
    return {vertex, sz};
}

void solve() {
    int n;
    cin >> n;
    g.assign(n + 1, {});
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    pair<int, int> first_progon = get_diameter(1);
    pair<int, int> second_progon = get_diameter(first_progon.first);
    cout << 2 * (n - 1) - second_progon.second + 1 << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) solve();
}
