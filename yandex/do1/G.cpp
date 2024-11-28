%:ifndef SEREGA
#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2,popcnt")
%:endif
#include <bits/stdc++.h>
using namespace std;
%:define int int64_t
const int MOD = 1e9 + 7;
int pluss(int x, int y) {
    return (0ll + x + y) % MOD;
}
struct Segtree {
    vector<vector<int>> tree;
    Segtree(int n, int k) : tree(2 * n - 1, vector<int>(k)) {}
    int get(int x, int lx, int rx, int l, int r, int k) {
        if (l > r) return 0;
        if (l == lx && r == rx) {
            return tree[x][k];
        }
        int m = (lx + rx) >> 1;
        int s1 = get(x + 1, lx, m, l, min(m, r), k);
        int s2 = get(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r, k);
        return s1 + s2;
    }
    void add(int x, int lx, int rx, int i, int k, int v) {
        if (lx == rx) {
            tree[x][k] = pluss(tree[x][k], v);
            return;
        }
        int m = (lx + rx) >> 1;
        if (i <= m) {
            add(x + 1, lx, m, i, k, v);
        } else {
            add(x + 2 * (m - lx + 1), m + 1, rx, i, k, v);
        }
        tree[x][k] = pluss(tree[x + 1][k], tree[x + 2 * (m - lx + 1)][k]);
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    Segtree seg(n + 1, k + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i]--;
    }
    for (int i = 0; i < n; ++i) {
        seg.add(0, 0, n - 1, a[i], 1, 1);
        for (int kk = 2; kk <= k; ++kk) {
            seg.add(0, 0, n - 1, a[i], kk, seg.get(0, 0, n - 1, a[i] + 1, n - 1, kk - 1));
        }
    }
    cout << seg.tree[0][k] << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
