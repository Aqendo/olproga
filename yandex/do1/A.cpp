#include <bits/stdc++.h>
using namespace std;

struct Segtree {
    vector<pair<int, int>> tree;
    int n;
    Segtree(vector<int>& a) : tree(2 * a.size() - 1, {INT_MIN, INT_MIN}), n(a.size()) { build(a, 0, 0, n - 1); }
    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx) {
            if (lx < a.size()) {
                tree[x] = {a[lx], lx};
            }
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, x + 1, lx, m);
        build(a, x + 2 * (m - lx + 1), m + 1, rx);
        tree[x] = max(tree[x + 1], tree[x + 2 * (m - lx + 1)]);
    }
    pair<int, int> get(int x, int lx, int rx, int l, int r) {
        if (l > r) return {INT_MIN, INT_MIN};
        if (lx == l && rx == r) {
            return tree[x];
        }
        int m = (lx + rx) >> 1;
        return max(get(x + 1, lx, m, l, min(m, r)), get(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r));
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    Segtree seg(a);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        auto [val, index] = seg.get(0, 0, n - 1, l - 1, r - 1);
        cout << val << ' ' << index + 1 << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}