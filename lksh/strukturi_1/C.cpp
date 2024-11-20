#include <bits/stdc++.h>

using namespace std;

struct Segtree {
    vector<vector<int64_t>> tree;
    int64_t n;
    Segtree(int64_t nn) : tree(4 * nn), n(nn) {}
    Segtree(int64_t nn, vector<int64_t>& a) : tree(4 * nn), n(nn) { build(a, 1, 0, n - 1); }
    static void combine(vector<int64_t>& to, vector<int64_t>& from1, vector<int64_t>& from2) {
        merge((from1).begin(), (from1).end(), (from2).begin(), (from2).end(), back_inserter(to));
    }
    void build(vector<int64_t>& a, int64_t x, int64_t lx, int64_t rx) {
        if (lx == rx) {
            if (lx < n) {
                tree[x] = {a[lx]};
            }
            return;
        }
        int64_t m = (lx + rx) >> 1;
        build(a, x << 1, lx, m);
        build(a, x << 1 | 1, m + 1, rx);
        combine(tree[x], tree[x << 1], tree[x << 1 | 1]);
    }
    void set(int64_t x, int64_t lx, int64_t rx, int64_t i, int64_t v) {
        if (lx == rx) {
            tree[x] = {v};
            return;
        }
        int64_t m = (lx + rx) >> 1;
        if (i <= m) {
            set(x << 1, lx, m, i, v);
        } else {
            set(x << 1 | 1, m + 1, rx, i, v);
        }
        combine(tree[x], tree[x << 1], tree[x << 1 | 1]);
    }
    int64_t get(int64_t x, int64_t lx, int64_t rx, int64_t l, int64_t r, int64_t mx) {
        if (l > r) {
            return 0;
        }
        if (lx == l && rx == r) {
            int64_t res = upper_bound((tree[x]).begin(), (tree[x]).end(), mx) - tree[x].begin();
            return res;
        }
        int64_t m = (lx + rx) >> 1;
        int64_t g1 = get(x << 1, lx, m, l, min(m, r), mx);
        int64_t g2 = get(x << 1 | 1, m + 1, rx, max(l, m + 1), r, mx);
        return g1 + g2;
    }
};

void solve() {
    int64_t n, m;
    cin >> n >> m;
    vector<int64_t> a(n);
    for (int64_t i = 0; i < n; ++i) {
        cin >> a[i];
    }
    Segtree seg(n, a);
    for (int64_t i = 0; i < m; ++i) {
        int64_t x, y, k, l;
        cin >> x >> y >> k >> l;
        cout << seg.get(1, 0, n - 1, x - 1, y - 1, l) - seg.get(1, 0, n - 1, x - 1, y - 1, k - 1) << '\n';
    }
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}