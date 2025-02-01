#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<vector<int>> g;
vector<array<int, 3>> ops;

int n, m, H;

vector<int> get_root, used;

void get_tin(int x, int root_of_subtree) {
    get_root[x] = root_of_subtree;
    used[x] = H;
    for (int u : g[x]) {
        if (used[u] != H) {
            get_tin(u, root_of_subtree);
        }
    }
}

void solve() {
    cin >> n >> m;
    g.assign(n + 1, {});
    ops.resize(m);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        ops[i] = {a, b, c};
    }
    get_root.assign(n + 1, {});
    used.assign(n + 1, {});

    for (H = 1; H <= n; ++H) {
        // cout << "now in " << H << '\n';
        used[H] = H;
        for (int i = 0; i < (int)g[H].size(); ++i) {
            get_tin(g[H][i], i);
        }
        vector<vector<int>> ans(g[H].size(), vector<int>(g[H].size()));
        vector<int> dopans(g[H].size());
        int already = 0;
        for (auto [a, b, c] : ops) {
            if (a != H && b != H) {
                // cout << "adding " << c << " to ans[" << g[H][get_root[b]] << "][" << g[H][get_root[a]] << "]\n";
                if (get_root[b] == get_root[a]) {
                    dopans[get_root[a]] += c;
                } else {
                    ans[get_root[b]][get_root[a]] += c;
                    // cout << "secondly adding " << c << " to ans[" << g[H][get_root[a]] << "][" << g[H][get_root[b]] << "]\n";
                    ans[get_root[a]][get_root[b]] += c;
                }
            } else if (a != H) {
                // cout << "dopans of " << c << " to " << g[H][get_root[a]] << endl;
                dopans[get_root[a]] += c;
            } else if (b != H) {
                // cout << "dopans of " << c << " to " << g[H][get_root[b]] << endl;
                dopans[get_root[b]] += c;
            } else {
                // cout << "petlya of " << c << endl;
                already += c;
            }
        }
        int res = already;
        for (int i = 0; i < (int)g[H].size(); ++i) {
            for (int j = i; j < (int)g[H].size(); ++j) {
                int temp = already;
                temp += ans[i][j];
                temp += dopans[i];
                if (i != j) {
                    temp += dopans[j];
                }
                // cout << g[H][i] << ' ' << g[H][j] << ": " << temp << '\n';
                res = max(res, temp);
            }
        }
        cout << res << ' ';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}