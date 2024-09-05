#include "bits/stdc++.h"

using namespace std;
#define int long long

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

vector<int> fenwick;
int n;
void upd_(int i, int x) {
    for (; i < n; i |= i + 1) {
        fenwick[i] += x;
    }
}
int get(int r) {
    int res = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) {
        res += fenwick[r];
    }
    return res;
}

void upd(int l, int r, int x) {
    upd_(l, x);
    if (r + 1 < n) {
        upd_(r + 1, -x);
    }
}

const int UNSET = INT_MAX;
// const int UNSET = 0;
int index_ = 0;
struct Segtree {
    vector<int> tree;
    vector<int> lazy;
    int n_;
    Segtree(vector<int>& a) : tree(4 * a.size()), n_(a.size()), lazy(4 * a.size(), UNSET) { build(a, 1, 0, n_ - 1); }
    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx) {
            if (lx < n_) {
                tree[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, x << 1, lx, m);
        build(a, x << 1 | 1, m + 1, rx);
    }

    int combine(int first, int second, int x) { return first + lazy[x << 1] + second + lazy[x << 1 | 1]; }

    void push(int x, int lx, int rx) {
        if (lx == rx) {
            return;
        }
        if (lazy[x] == UNSET) return;
        printf("got x=%lld, [%lld..%lld], lazy[x]=%lld\n", x, lx, rx, lazy[x]);
        if (lazy[x] == -1) {
            int m = (lx + rx) >> 1;
            if (lazy[x << 1] != UNSET) {
                upd(lx, m, index_ - lazy[x << 1]);
            }
            if (lazy[x << 1 | 1] != UNSET) {
                upd(m + 1, rx, index_ - lazy[x << 1 | 1]);
            }
            lazy[x << 1] = UNSET;
            lazy[x << 1 | 1] = UNSET;
        } else {
            int m = (lx + rx) >> 1;
            lazy[x << 1] = min(lazy[x << 1], lazy[x]);
            lazy[x << 1 | 1] = min(lazy[x << 1 | 1], lazy[x]);
        }
        lazy[x] = UNSET;
    }
    void add(int x, int lx, int rx, int l, int r, int timestamp) {
        if (l > r) return;
        push(x, lx, rx);
        if (lx == l && rx == r) {
            lazy[x] = min(lazy[x], timestamp);
            push(x, lx, rx);
            return;
        }
        int m = (lx + rx) >> 1;
        add(x << 1, lx, m, l, min(r, m), timestamp);
        add(x << 1 | 1, m + 1, rx, max(l, m + 1), r, timestamp);
    }
    void get(int x, int lx, int rx, int i) {
        push(x, lx, rx);
        if (lx == rx) {
            return;
        }
        int m = (lx + rx) >> 1;
        if (i <= m) {
            get(x << 1, lx, m, i);
        } else {
            get(x << 1 | 1, m + 1, rx, i);
        }
    }
};

void solve() {
    int m;
    cin >> n >> m;
    fenwick.assign(n, {});
    vector<int> unsets(n, UNSET);
    Segtree seg(unsets);
    for (index_ = 0; index_ < m; ++index_) {
        char move;
        int l, r;
        cin >> move >> l >> r;
        l--;
        r--;
        if (move == '+') {
            seg.add(1, 0, n - 1, l, r, index_);
        } else {
            seg.add(1, 0, n - 1, l, r, -1);
        }
    }
    seg.add(1, 0, n - 1, 0, n - 1, -1);
    for (int i = 0; i < n; ++i) {
        seg.get(1, 0, n - 1, i);
    }
    for (int i = 0; i < n; ++i) {
        cout << get(i) << '\n';
    }
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
