#include <bits/stdc++.h>
using namespace std;
%:define int int64_t

vector<int> mt;
vector<vector<int>> g;
vector<int> used;
int timer = 0;

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
    g.assign(n + 1, {});
    used.assign(n + 1, {});
    mt.assign(m + 1, -1);
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        while (x != 0) {
            g[i].push_back(x);
            cin >> x;
        }
    }
    int answer = 0;
    for (int i = 1; i <= n; ++i) {
        timer += 1;
        if (try_kuhn(i)) {
            answer += 1;
        }
    }
    cout << answer << '\n';
    for (int i = 1; i <= m; ++i) {
        if (mt[i] != -1) {
            cout << mt[i] << ' ' << i << "\n";
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
