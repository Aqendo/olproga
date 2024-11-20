#include <bits/stdc++.h>

using namespace std;

struct Segtree {
    vector<int64_t> tree;
    int64_t n;
    Segtree(int64_t nn) : tree(4 * nn, 0), n(nn) {}
    Segtree(int64_t nn, vector<int64_t>& a) : tree(4 * nn, 0), n(nn) { build(a, 1, 0, n - 1); }
    void build(vector<int64_t>& a, int64_t x, int64_t lx, int64_t rx) {
        if (lx == rx) {
            if (lx < n) {
                tree[x] = a[lx] > 0;
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
            tree[x] = v > 0;
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
    int64_t get_full_count(int64_t x, int64_t lx, int64_t rx, int64_t l, int64_t r) {
        if (l > r) return 0;
        if (lx == l && rx == r) return tree[x];
        int64_t m = (lx + rx) >> 1;
        int64_t s1 = get_full_count(x << 1, lx, m, l, min(m, r));
        int64_t s2 = get_full_count(x << 1 | 1, m + 1, rx, max(l, m + 1), r);
        return s1 + s2;
    }
    int64_t get_ith(int64_t x, int64_t lx, int64_t rx, int64_t cnt_ones) {
        if (lx == rx) return lx;
        int64_t cnt_right = tree[x << 1 | 1];
        int64_t m = (lx + rx) >> 1;
        if (cnt_right >= cnt_ones) {
            return get_ith(x << 1 | 1, m + 1, rx, cnt_ones);
        }
        return get_ith(x << 1, lx, m, cnt_ones - cnt_right);
    }
};
void solve() {
    int64_t n;
    cin >> n;
    vector<pair<int64_t, int64_t>> ops(n);
    vector<int64_t> vals;
    for (int64_t i = 0; i < n; ++i) {
        cin >> ops[i].first >> ops[i].second;
        if (ops[i].first == 1) {
            vals.push_back(ops[i].second);
        }
    }
    int64_t index = 0;
    map<int64_t, int64_t> coords;
    sort(vals.begin(), vals.end());
    for (int64_t i : vals) {
        if (!coords.count(i)) {
            coords[i] = index++;
        }
    }
    vector<int64_t> vals_(index);
    for (auto& [l, r] : coords) {
        vals_[r] = l;
    }
    int64_t nn = (int64_t)vals_.size();
    Segtree seg(nn);
    for (auto& [move, data] : ops) {
        if (move == 1) {
            seg.set(1, 0, nn - 1, coords[data], 1);
        } else if (move == -1) {
            seg.set(1, 0, nn - 1, coords[data], 0);
        } else {
            cout << vals_[seg.get_ith(1, 0, nn - 1, data)] << '\n';
        }
    }
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}