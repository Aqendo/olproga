// #pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define int int64_t
using namespace std;

#ifdef SEREGA
#include "debug.h"
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#else
#define debug(...)
#endif

struct Mass {
    int a1, k;

    Mass& operator+=(const Mass& m1) {
        a1 += m1.a1;
        k += m1.k;
        return *this;
    }

    bool operator<(const Mass& m1) const {
        if (a1 != m1.a1) return a1 < m1.a1;
        return k < m1.k;
    }

    Mass operator+(const Mass& m1) { return {a1 + m1.a1, k + m1.k}; }
};

struct Segtree {
    vector<int> tree;
    vector<Mass> lazy;
    int n;

    Segtree(vector<int>& a)
        : tree(4 * a.size()), lazy(4 * a.size()), n(a.size()) {
        build(a, 1, 0, n - 1);
    }

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

    void push(int x, int lx, int rx) {
        if (lx == rx) {
            tree[x] = max(tree[x], lazy[x].a1);
            lazy[x] = {0, 0};
            return;
        }
        int m = (lx + rx) >> 1;
        int a2 = lazy[x].a1 + lazy[x].k * (m - lx + 1);
        lazy[x << 1] = max(lazy[x << 1], lazy[x]);
        lazy[x << 1 | 1] = max(lazy[x << 1 | 1], {a2, lazy[x].k});
        lazy[x] = {0, 0};
        tree[x << 1] = combine(x << 1, lx, m);
        tree[x << 1 | 1] = combine(x << 1 | 1, m + 1, rx);
        tree[x] = combine(x, lx, rx);
    }

    int combine(int x, int lx, int rx) {
        int len = rx - lx + 1;
        if (lx == rx) return tree[x];
        return tree[x << 1] + tree[x << 1 | 1] +
               apply(lazy[x].a1, lazy[x].k, len);
    }

    int apply(int a1, int k, int len) {
        int res = (2 * a1 + k * (len - 1)) / 2 * len;
        assert(res >= 0);
        return res;
    }

    void add(int x, int lx, int rx, int l, int r, int a1, int k) {
        if (l > r) return;
        push(x, lx, rx);
        if (lx == l && rx == r) {
            lazy[x] = max(lazy[x], {a1, k});
            push(x, lx, rx);
            tree[x] = combine(x, lx, rx);
            return;
        }
        int m = (lx + rx) >> 1;
        int len = max<int>(0, m - l + 1);
        add(x << 1, lx, m, l, min(r, m), a1, k);
        add(x << 1 | 1, m + 1, rx, max(m + 1, l), r, a1 + len * k, k);

        tree[x] = combine(x, lx, rx);
    }

    int get(int x, int lx, int rx, int l, int r) {
        if (l > r) return 0;
        push(x, lx, rx);
        if (lx == l && rx == r) return tree[x];
        int m = (lx + rx) >> 1;
        int s1 = get(x << 1, lx, m, l, min(m, r));
        int s2 = get(x << 1 | 1, m + 1, rx, max(l, m + 1), r);
        int len = rx - lx + 1;
        return s1 + s2 + apply(lazy[x].a1, lazy[x].k, len);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> pref(n);
    Segtree seg(pref);
    // seg.add(1, 0, n - 1, 7, 7, 1, 1);
    //
    // for (int i = 0; i < n; ++i) {
    //   cout << seg.get(1, 0, n - 1, i, i) << ' ';
    // }
    // cout << '\n';
    // seg.add(1, 0, n - 1, 0, 2, 1, 2);
    // for (int i = 0; i < n; ++i) {
    //   cout << seg.get(1, 0, n - 1, i, i) << ' ';
    // }
    // cout << '\n';
    // exit(0);
    for (int i = 1; i < n; ++i) {
        if (a[i] != 0) {
            // debug(1, 0, n - 1, i, min(n - 1, i + a[i] - 1), 1, 1);
            seg.add(1, 0, n - 1, i, min(n - 1, i + a[i] - 1), 1, 1);
            // for (int i1 = 0; i1 < n; ++i1) {
            //   cout << seg.get(1, 0, n - 1, i1, i1) << ' ';
            // }
            // cout << '\n';
            // for (int j = 1; j <= a[i]; ++j) {
            //   pref[i + j - 1] = max(pref[i + j - 1], j);
            // }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << seg.get(1, 0, n - 1, i, i) << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
