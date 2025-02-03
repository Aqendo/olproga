#include <bits/stdc++.h>
using namespace std;
%:define int int64_t

const int N = 1000 + 78;

vector<int> g[N];

int mt[N], used[N], timer = 0;

bool try_kuhn(int x) {
    if (used[x] == timer) return false;
    used[x] = timer;
    for (int u : g[x]) {
        if (mt[u] == -1 || try_kuhn(mt[u])) {
            mt[u] = x;
            return true;
        }
    }
    return false;
}

void solve() {
    int n, m;
    cin >> n >> m;
    memset(mt, -1, sizeof(mt));
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }
    for (int i = 1; i <= n; ++i) {
        timer += 1;
        try_kuhn(i);
    }
    vector<pair<int, int>> edges;
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        cnt += mt[i] == -1;
    }
    cout << cnt << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
