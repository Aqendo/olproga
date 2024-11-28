#include <bits/stdc++.h>
using namespace std;
%:define int int64_t
struct Segtree {
    vector<int> tree;
    Segtree(int n) : tree(2 * n - 1) {}
    void add(int x, int lx, int rx, int i, int v) {
        if (lx == rx) {
            tree[x] += v;
            return;
        }
        int m = (lx + rx) >> 1;
        if (i <= m) {
            add(x + 1, lx, m, i, v);
        } else {
            add(x + 2 * (m - lx + 1), m + 1, rx, i, v);
        }
        tree[x] = tree[x + 1] + tree[x + 2 * (m - lx + 1)];
    }
    int get(int x, int lx, int rx, int l, int r) {
        if (l > r) return 0;
        if (lx == l && rx == r) {
            return tree[x];
        }
        int m = (lx + rx) >> 1;
        int s1 = get(x + 1, lx, m, l, min(m, r));
        int s2 = get(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r);
        return s1 + s2;
    }
};
void solve() {
    int n;
    cin >> n;
    Segtree seg(n + 2);
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        seg.add(0, 0, n, i, t);
        seg.add(0, 0, n, i + 1, -t);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        char move;
        cin >> move;
        if (move == 'g') {
            int index;
            cin >> index;
            cout << seg.get(0, 0, n, 0, index - 1) << '\n';
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            seg.add(0, 0, n, l - 1, x);
            seg.add(0, 0, n, r, -x);
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
