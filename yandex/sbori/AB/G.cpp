#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> sizes, parent, mx, mn;
    void init(int n) {
        sizes.assign(n, 1);
        parent.assign(n, {});
        mx.assign(n, INT_MIN);
        mn.assign(n, INT_MAX);
        iota(parent.begin(), parent.end(), 0);
        iota(mx.begin(), mx.end(), 0);
        iota(mn.begin(), mn.end(), 0);
    }
    int getp(int x) {
        if (parent[x] == x) return x;
        return parent[x] = getp(parent[x]);
    }
    int getmn(int x) {
        x = getp(x);
        return mn[x];
    }
    int getmx(int x) {
        x = getp(x);
        return mx[x];
    }
    bool unite(int a, int b) {
        a = getp(a);
        b = getp(b);
        if (a == b) return false;
        if (sizes[a] < sizes[b]) swap(a, b);
        mx[a] = max(mx[a], mx[b]);
        mn[a] = min(mn[a], mn[b]);
        sizes[a] += sizes[b];
        parent[b] = a;
        return true;
    }
};

bool has[2000][2000];

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            has[i][j] = true;
        }
    }
    vector<DSU> vertical(m), horizontal(n);
    for (int i = 0; i < m; ++i) {
        vertical[i].init(n);
    }
    for (int i = 0; i < n; ++i) {
        horizontal[i].init(m);
    }
    for (int i = 0; i < q; ++i) {
        char move;
        int x, y;
        cin >> move >> x >> y;
        x--;
        y--;
        if (move == 'c') {
            if (y - 1 >= 0 && !has[x][y - 1]) {
                horizontal[x].unite(y - 1, y);
            }
            if (y + 1 < m && !has[x][y + 1]) {
                horizontal[x].unite(y, y + 1);
            }
            if (x - 1 >= 0 && !has[x - 1][y]) {
                vertical[y].unite(x, x - 1);
            }
            if (x + 1 < n && !has[x + 1][y]) {
                vertical[y].unite(x, x + 1);
            }
            has[x][y] = false;
        } else if (move == 'u') {
            if (x - 1 >= 0) {
                int ans = vertical[y].getmn(x - 1);
                if (has[ans][y]) {
                    cout << ans + 1 << ' ' << y + 1 << '\n';
                    continue;
                }
                if (ans - 1 >= 0) {
                    cout << ans << ' ' << y + 1 << '\n';
                } else {
                    cout << -1 << '\n';
                }
            } else {
                cout << -1 << '\n';
            }
        } else if (move == 'd') {
            if (x + 1 < n) {
                int ans = vertical[y].getmx(x + 1);
                if (has[ans][y]) {
                    cout << ans + 1 << ' ' << y + 1 << '\n';
                    continue;
                }
                if (ans + 1 < n) {
                    cout << ans + 2 << ' ' << y + 1 << '\n';
                } else {
                    cout << -1 << '\n';
                }
            } else {
                cout << -1 << '\n';
            }
        } else if (move == 'l') {
            if (y - 1 >= 0) {
                int ans = horizontal[x].getmn(y - 1);
                if (has[x][ans]) {
                    cout << x + 1 << ' ' << ans + 1 << '\n';
                    continue;
                }
                if (ans - 1 >= 0) {
                    cout << x + 1 << ' ' << ans << '\n';
                } else {
                    cout << -1 << '\n';
                }
            } else {
                cout << -1 << '\n';
            }
        } else {
            if (y + 1 < m) {
                int ans = horizontal[x].getmx(y + 1);
                if (has[x][ans]) {
                    cout << x + 1 << ' ' << ans + 1 << '\n';
                    continue;
                }
                if (ans + 1 < m) {
                    cout << x + 1 << ' ' << ans + 2 << '\n';
                } else {
                    cout << -1 << '\n';
                }
            } else {
                cout << -1 << '\n';
            }
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}