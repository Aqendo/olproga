#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<int> l, r;
vector<vector<int>> g;

struct Node {
    int mx;
    int add;
};

Node dfs(int x, int p = -1) {
    int mx = 0;
    int toadd = 0;
    vector<int> offset(g[x].size());
    vector<int> mxs(g[x].size());
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u != p) {
            auto [mxdfs, add] = dfs(u, x);
            toadd += add;
            mxs[i] = mxdfs;
            offset[i] += add;
        }
    }
    mx = l[x] + toadd;
    vector<int> current(g[x].size());
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u != p) {
            current[i] = mxs[i] + toadd - offset[i];
            if (current[i] > mx) {
                mx = current[i];
            }
        }
    }
    int remain = mx - (r[x] + toadd);
    if (remain > 0) {
        int mn = r[x] + toadd;
        int current_toadd = 0;
        for (int i = 0; i < (int)g[x].size(); ++i) {
            if (g[x][i] != p) {
                current_toadd += max<int>(0, current[i] - mn);
            }
        }
        // current_toadd += (r[x] + toadd) - mn;
        mx = mn + current_toadd;
        toadd += current_toadd;
    }
    return {mx, toadd};
}

void solve() {
    int n;
    cin >> n;
    g.assign(n + 1, {});
    l.assign(n + 1, {});
    r.assign(n + 1, {});
    int start = 1;
    for (int i = 1; i <= n; ++i) {
        cin >> l[i] >> r[i];
        if (r[i] > r[start]) start = i;
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cout << dfs(start).mx << endl;
    // for (int i = 1; i <= n; ++i) {
    //     cout << dfs(i).mx << endl;
    // }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}