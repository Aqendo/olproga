#include <bits/stdc++.h>

using namespace std;

struct Segtree {
    vector<int64_t> tree;
    int64_t n;

    Segtree(int64_t nn) : tree(4 * nn, 1), n(nn) {}

    Segtree(int64_t nn, vector<int64_t>& a) : tree(4 * nn, 1), n(nn) {
        build(a, 1, 0, n - 1);
    }

    void build(vector<int64_t>& a, int64_t x, int64_t lx, int64_t rx) {
        if (lx == rx) {
            if (lx < n) {
                tree[x] = a[lx] == 0;
            }
            return;
        }
        int64_t m = (lx + rx) >> 1;
        build(a, x << 1, lx, m);
        build(a, x << 1 | 1, m + 1, rx);
        tree[x] = tree[x << 1] + tree[x << 1 | 1];
    }

    void set(int64_t x, int64_t lx, int64_t rx, int64_t i, int64_t v) {
        if (lx == rx) {
            tree[x] = v == 0;
            return;
        }
        int64_t m = (lx + rx) >> 1;
        if (i <= m) {
            set(x << 1, lx, m, i, v);
        } else {
            set(x << 1 | 1, m + 1, rx, i, v);
        }
        tree[x] = tree[x << 1] + tree[x << 1 | 1];
    }

    int64_t get_full_count(int64_t x, int64_t lx, int64_t rx, int64_t l,
                           int64_t r) {
        if (l > r) return 0;
        if (lx == l && rx == r) return tree[x];
        int64_t m = (lx + rx) >> 1;
        int64_t s1 = get_full_count(x << 1, lx, m, l, min(m, r));
        int64_t s2 = get_full_count(x << 1 | 1, m + 1, rx, max(l, m + 1), r);
        return s1 + s2;
    }

    int64_t get_ith(int64_t x, int64_t lx, int64_t rx, int64_t cnt_zero) {
        if (lx == rx) return (tree[x] == 1 ? lx : (int64_t)1e9);
        int64_t cnt_left = tree[x << 1];
        int64_t m = (lx + rx) >> 1;
        if (cnt_left < cnt_zero) {
            return get_ith(x << 1 | 1, m + 1, rx, cnt_zero - cnt_left);
        } else {
            return get_ith(x << 1, lx, m, cnt_zero);
        }
    }
};

void solve() {
    int64_t n, q;
    cin >> n;
    vector<int64_t> a(n);
    for (int64_t i = 0; i < n; ++i) cin >> a[i];
    Segtree seg(n, a);
    cin >> q;
    int64_t full = seg.get_full_count(1, 0, n - 1, 0, n - 1);
    for (int64_t i = 0; i < q; ++i) {
        char move;
        cin >> move;
        if (move == 'u') {
            int64_t ind, v;
            cin >> ind >> v;
            seg.set(1, 0, n - 1, ind - 1, v);
            full = seg.get_full_count(1, 0, n - 1, 0, n - 1);
            a[ind - 1] = v;
        } else {
            int64_t l, r, k;
            cin >> l >> r >> k;
            l--;
            r--;
            int64_t before = seg.get_full_count(1, 0, n - 1, 0, l - 1);
            int64_t res = seg.get_ith(1, 0, n - 1, before + k);
            if (res > r || full < before + k) {
                cout << "-1 ";
            } else {
                cout << res + 1 << ' ';
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}