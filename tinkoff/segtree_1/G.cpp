#include "bits/stdc++.h"
using namespace std;
#define int long long
#ifdef SEREGA
#include "/home/ser/olproga/debug.h"
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

#ifndef SEREGA
#define printf(...)
#define debug(...)
#endif

struct Segtree {
    vector<int> tree;
    vector<int> lazy;
    int n;
    Segtree(vector<int>& a) : n(a.size()), tree(4 * a.size(), LLONG_MIN), lazy(4 * a.size()) { build(a, 1, 0, n - 1); }
    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx) {
            if (lx < n) {
                tree[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, x << 1, lx, m);
        build(a, x << 1 | 1, m + 1, rx);
        tree[x] = max(tree[x << 1], tree[x << 1 | 1]);
    }
    void add(int x, int lx, int rx, int l, int r, int val) {
        if (l > r) return;
        if (l == lx && r == rx) {
            lazy[x] += val;
            tree[x] += val;
            return;
        }
        int m = (lx + rx) >> 1;
        add(x << 1, lx, m, l, min(m, r), val);
        add(x << 1 | 1, m + 1, rx, max(m + 1, l), r, val);
        tree[x] = max(tree[x << 1], tree[x << 1 | 1]) + lazy[x];
    }
    int get(int x, int lx, int rx, int l, int r) {
        if (l > r) return LLONG_MIN;
        if (l == lx && rx == r) return tree[x];
        int m = (lx + rx) >> 1;
        int s1 = get(x << 1, lx, m, l, min(m, r));
        int s2 = get(x << 1 | 1, m + 1, rx, max(m + 1, l), r);
        return max(s1, s2) + lazy[x];
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
        char move;
        cin >> move;
        if (move == 'm') {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            cout << seg.get(1, 0, n - 1, l, r) << '\n';
        } else {
            int l, r, add;
            cin >> l >> r >> add;
            l--;
            r--;
            seg.add(1, 0, n - 1, l, r, add);
        }
    }
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
