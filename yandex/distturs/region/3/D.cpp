#include "bits/stdc++.h"
#define int int64_t
using namespace std;

vector<vector<int>> g;
vector<pair<int, int>> posilki;
vector<int> used;
vector<int> tin;
set<vector<int>> already;
bool good = true;
int timer = 0;
void dfs(int x) {
    used[x] = true;
    tin[x] = timer++;
    for (int u : g[x]) {
        if (!used[u]) {
            dfs(u);
        }
    }
}
int n, m;
long long cnt = 0;
void reiterate(int index = 1) {
    if (index == n + 1) {
        used.assign(n + 1, {});
        tin.assign(n + 1, {});
        timer = 0;
        // for (int i = 1; i <= n; ++i) {
        //     cout << "[";
        //     for (int j : g[i]) {
        //         cout << j << ',';
        //     }
        //     cout << "] ";
        // }
        // cout << '\n';
        dfs(1);
        good = true;
        for (auto& [u, v] : posilki) {
            good &= (tin[u] < tin[v]);
        }
        if (good) {
            already.insert(tin);
        }
        return;
    }
    do {
        reiterate(index + 1);
    } while (next_permutation(g[index].begin(), g[index].end()));
}
void solve() {
    cin >> n >> m;
    g.assign(n + 1, {});
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 1; i <= n; ++i) {
        sort(g[i].begin(), g[i].end());
    }
    posilki.assign(m, {});
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        posilki[i] = {a, b};
    }
    reiterate();
    cout << already.size() << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
