#include "bits/stdc++.h"
using namespace std;
#define int int64_t
struct Node {
    int mx, mn, v;
};
struct Segtree {
    vector<Node> tree;
    vector<int> lazy;
    Segtree(const vector<int>& arr) : tree(2 * arr.size() - 1), lazy(2 * arr.size() - 1) { build(arr, 0, 0, arr.size() - 1); }
    void build(const vector<int>& arr, int x, int lx, int rx) {
        if (lx == rx) {
            tree[x] = {.mx = arr[lx], .mn = arr[lx], .v = arr[lx]};
            return;
        }
        int m = (lx + rx) >> 1;
        build(arr, x + 1, lx, m);
        build(arr, x + 2 * (m - lx + 1), m + 1, rx);
        tree[x] = combine(tree[x + 1], tree[x + 2 * (m - lx + 1)]);
    }
    Node combine(Node& l, Node& r) { return {.mx = max(l.mx, r.mx), .mn = min(l.mn, r.mn), .v = l.v + r.v}; }
    void update(int x, int lx, int rx, int i, int v) {
        int m = (lx + rx) >> 1;
        push(x, lx, m, rx);
        if (lx == rx) {
            tree[x].mx = v;
            tree[x].mn = v;
            tree[x].v = v;
            lazy[x] = 0;
            return;
        }
        if (i <= m) {
            update(x + 1, lx, m, i, v);
        } else {
            update(x + 2 * (m - lx + 1), m + 1, rx, i, v);
        }
        tree[x] = combine(tree[x + 1], tree[x + 2 * (m - lx + 1)]);
    }

    Node sum(int x, int lx, int rx, int l, int r) {
        if (l > r) return {.mx = 0, .mn = 0, .v = 0};
        int m = (lx + rx) >> 1;
        push(x, lx, m, rx);
        if (l == lx && r == rx) {
            return tree[x];
        }
        Node s1 = sum(x + 1, lx, m, l, min(m, r));
        Node s2 = sum(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r);
        return combine(s1, s2);
    }
    void massop(int x, int lx, int rx, int l, int r, int mod) {
        if (l > r) return;
        int m = (lx + rx) >> 1;
        push(x, lx, m, rx);
        if (tree[x].mx < mod) {
            return;
        }
        if (l == lx && r == rx && tree[x].mx / mod == tree[x].mn / mod) {
            int todel = (tree[x].mx / mod) * mod;
            tree[x].v -= todel * (rx - lx + 1);
            tree[x].mx -= todel;
            tree[x].mn -= todel;
            lazy[x] -= todel;
            return;
        }
        massop(x + 1, lx, m, l, min(m, r), mod);
        massop(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r, mod);
        tree[x] = combine(tree[x + 1], tree[x + 2 * (m - lx + 1)]);
    }
    void push(int x, int lx, int m, int rx) {
        if (lx == rx) {
            lazy[x] = 0;
            return;
        }
        tree[x + 1].v += lazy[x] * (m - lx + 1);
        tree[x + 2 * (m - lx + 1)].v += lazy[x] * (rx - m);
        lazy[x + 1] += lazy[x];
        lazy[x + 2 * (m - lx + 1)] += lazy[x];
        lazy[x] = 0;
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
        int move;
        cin >> move;
        if (move == 1) {
            int index, x;
            cin >> index >> x;
            seg.update(0, 0, n - 1, index - 1, x);
        } else if (move == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            seg.massop(0, 0, n - 1, l - 1, r - 1, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.sum(0, 0, n - 1, l - 1, r - 1).v << '\n';
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}