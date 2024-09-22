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
    vector<int> tree, lazy;
    int n;
    Segtree(vector<int>& a) : n(a.size()), tree(4 * a.size()), lazy(4 * a.size()) { build(a, 1, 0, n - 1); }
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
        tree[x] = tree[x << 1] + tree[x << 1 | 1];
    }
    void add(int x, int lx, int rx, int i, int v) {
        if (lx == rx) {
            tree[x] += v;
            return;
        }
        int m = (lx + rx) >> 1;
        if (i <= m) {
            add(x << 1, lx, m, i, v);
        } else {
            add(x << 1 | 1, m + 1, rx, i, v);
        }
        tree[x] = tree[x << 1] + tree[x << 1 | 1];
    }
    int get(int x, int lx, int rx, int l, int r) {
        if (l > r) return 0;
        if (l == lx && rx == r) return tree[x];
        int m = (lx + rx) >> 1;
        int s1 = get(x << 1, lx, m, l, min(m, r));
        int s2 = get(x << 1 | 1, m + 1, rx, max(m + 1, l), r);
        return s1 + s2;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> razn(n + 1);
    cin >> razn[0];
    int t = razn[0];
    for (int i = 1; i < n; ++i) {
        razn[i] = -t;
        cin >> t;
        razn[i] += t;
    }
    debug(razn);
    int q;
    cin >> q;
    Segtree seg(razn);
    for (int i = 0; i < q; ++i) {
        char move;
        cin >> move;
        if (move == 'a') {
            int l, r, x;
            cin >> l >> r >> x;
            l--;
            r--;
            seg.add(1, 0, n, l, x);
            // seg.add(1, 0, n, l + 1, -x);
            seg.add(1, 0, n, r + 1, -x);
            // seg.add(1, 0, n, r + 1, +x);
        } else {
            int index;
            cin >> index;
            cout << seg.get(1, 0, n, 0, index - 1) << '\n';
        }
    }
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
