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
    vector<int> changed;
    vector<int> added;
    int n;
    Segtree(vector<int>& a) : tree(4 * a.size()), changed(4 * a.size(), -69), added(4 * a.size()), n(a.size()) { build(a, 1, 0, n - 1); }
    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx) {
            tree[x] = a[lx];
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, x << 1, lx, m);
        build(a, x << 1 | 1, m + 1, rx);
        tree[x] = tree[x << 1] + tree[x << 1 | 1];
    }

    void push(int x, int lx, int rx) {
        // debug("x=", x, lx, rx);
        if (lx == rx) {
            if (changed[x] != -69) {
                tree[x] = changed[x];
            }
            // debug("was", tree[x]);
            // debug("adder", added[x]);
            tree[x] += added[x];

            changed[x] = -69;
            added[x] = 0;
            return;
        }
        int m = (lx + rx) >> 1;
        int len1 = m - lx + 1;
        int len2 = rx - m;
        if (changed[x] != -69) {
            added[x << 1] += added[x];
            changed[x << 1] = changed[x];

            changed[x << 1 | 1] = changed[x];
            added[x << 1 | 1] += added[x];

            // debug("1:", len1, changed[x << 1], added[x << 1]);
            tree[x << 1] = len1 * (changed[x << 1] + added[x << 1]);
            // debug("2:", len2, changed[x << 1 | 1], added[x << 1 | 1]);
            tree[x << 1 | 1] = len2 * (changed[x << 1 | 1] + added[x << 1 | 1]);
            // debug(tree[x << 1], tree[x << 1 | 1]);
            added[x] = 0;
            changed[x] = -69;
            if (len1 == 1) {
                added[x << 1] = 0;
                changed[x << 1] = -69;
            }
            if (len2 == 1) {
                added[x << 1 | 1] = 0;
                changed[x << 1 | 1] = -69;
            }

            // debug("now added[x<<1]:", added[x << 1], "added[x<<1|1]:", added[x << 1 | 1]);
            // debug("now changed[x<<1]:", changed[x << 1], "changed[x<<1|1]:", changed[x << 1 | 1]);
            tree[x] = tree[x << 1] + tree[x << 1 | 1];
        } else {
            if (len1 != 1) {
                added[x << 1] += added[x];
            }
            if (len2 != 1) {
                added[x << 1 | 1] += added[x];
            }
            tree[x << 1] += added[x] * len1;
            tree[x << 1 | 1] += added[x] * len2;
            added[x] = 0;
            // debug(tree[x << 1], tree[x << 1 | 1]);
            // debug("now added[x<<1]:", added[x << 1], "added[x<<1|1]:", added[x << 1 | 1]);
            // debug("now changed[x<<1]:", changed[x << 1], "changed[x<<1|1]:", changed[x << 1 | 1]);

            tree[x] = tree[x << 1] + tree[x << 1 | 1];
        }
    }

    void change(int x, int lx, int rx, int l, int r, int to_what) {
        if (l > r) return;
        push(x, lx, rx);
        if (l == lx && r == rx) {
            changed[x] = to_what;
            added[x] = 0;
            push(x, lx, rx);
            // debug("treenow", tree[x]);
            return;
        }
        int m = (lx + rx) >> 1;
        change(x << 1, lx, m, l, min(m, r), to_what);
        change(x << 1 | 1, m + 1, rx, max(m + 1, l), r, to_what);
        tree[x] = tree[x << 1] + tree[x << 1 | 1];
    }

    void add(int x, int lx, int rx, int l, int r, int to_add) {
        if (l > r) return;
        push(x, lx, rx);
        if (l == lx && r == rx) {
            added[x] += to_add;
            push(x, lx, rx);
            return;
        }
        int m = (lx + rx) >> 1;
        add(x << 1, lx, m, l, min(m, r), to_add);
        add(x << 1 | 1, m + 1, rx, max(m + 1, l), r, to_add);
        tree[x] = tree[x << 1] + tree[x << 1 | 1];
    }

    int get(int x, int lx, int rx, int l, int r) {
        if (l > r) return 0;
        push(x, lx, rx);
        if (l == lx && r == rx) return tree[x];
        int m = (lx + rx) >> 1;
        int s1 = get(x << 1, lx, m, l, min(m, r));
        int s2 = get(x << 1 | 1, m + 1, rx, max(m + 1, l), r);
        return s1 + s2;
    }
};

void print(Segtree& seg) {
    for (int i = 0; i < seg.n; ++i) {
        // debug("\n\nSTART", i);
        cout << seg.get(1, 0, seg.n - 1, i, i) << ' ';
        // debug("END", i, "\n\n");
    }
    cout << '\n';
}
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = 0;
    }
    Segtree seg(a);
    for (int i = 0; i < m; ++i) {
        int move;
        cin >> move;
        if (move == 1) {
            int l, r, v;
            cin >> l >> r >> v;
            seg.change(1, 0, n - 1, l, r - 1, v);
            print(seg);
            print(seg);
            print(seg);
            print(seg);
            debug();
            // change to
        } else if (move == 2) {
            int l, r, v;
            cin >> l >> r >> v;
            // if (l == 1 && r == 5) {
            // debug("THIS");
            // }
            seg.add(1, 0, n - 1, l, r - 1, v);
            // if (l == 1 && r == 5) {
            // debug("THIS ENDED");
            // }
            print(seg);
            print(seg);
            print(seg);
            print(seg);
            debug();
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.get(1, 0, n - 1, l, r - 1) << '\n';
            print(seg);
            print(seg);
            print(seg);
            print(seg);
            debug();
        }
    }
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
