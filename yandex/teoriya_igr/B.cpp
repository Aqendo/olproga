#include <bits/stdc++.h>
using namespace std;
%:define int int64_t
const int N = 1e5 + 78;

vector<int> g[N];

int n, m, used[N], answer[N];
vector<int> topsort;

void gettopsort(int x) {
    used[x] = true;
    for (int u : g[x]) {
        if (!used[u]) {
            gettopsort(u);
        }
    }
    topsort.push_back(x);
}

void dfs(int x) {
    used[x] = 1;
    set<int> remain;
    for (int i = 0; i <= (int)g[x].size(); ++i) {
        remain.insert(i);
    }
    for (int u : g[x]) {
        if (!used[u]) {
            dfs(u);
            remain.erase(answer[u]);
        }
    }
    answer[x] = *remain.begin();
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            gettopsort(i);
        }
    }
    memset(used, 0, sizeof(used));
    for (int x : topsort) {
        set<int> remain;
        for (int i = 0; i <= (int)g[x].size(); ++i) {
            remain.insert(i);
        }
        for (int u : g[x]) {
            remain.erase(answer[u]);
        }
        answer[x] = *remain.begin();
    }
    for (int i = 1; i <= n; ++i) {
        cout << answer[i] << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
