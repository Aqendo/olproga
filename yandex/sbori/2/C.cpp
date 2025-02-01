#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<array<int, 3>> mons;

struct Node {
    int mx;
    int lazy;
    Node combine(const Node &r) {
        return {
            .mx = max(mx, r.mx)};
    }
};

struct Segtree {
    vector<Node> tree;
    void init(int n) {
        tree.assign(2 * n - 1, {-int(1e9), 0});
    }
    void push(int x, int lx, int m, int rx) {
        if (lx == rx) {
            tree[x].lazy = 0;
            return;
        }
        tree[x + 1].mx += tree[x].lazy;
        tree[x + 1].lazy += tree[x].lazy;
        tree[x + 2 * (m - lx + 1)].mx += tree[x].lazy;
        tree[x + 2 * (m - lx + 1)].lazy += tree[x].lazy;
        tree[x].lazy = 0;
    }
    void add(int x, int lx, int rx, int l, int r, int toadd) {
        if (l > r) return;
        int m = (lx + rx) >> 1;
        push(x, lx, m, rx);
        if (l == lx && r == rx) {
            tree[x].lazy += toadd;
            tree[x].mx += toadd;
            return;
        }
        add(x + 1, lx, m, l, min(m, r), toadd);
        add(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r, toadd);
        tree[x] = tree[x + 1].combine(tree[x + 2 * (m - lx + 1)]);
    }
    int mx(int x, int lx, int rx, int l, int r) {
        if (l > r) return -1e9;
        int m = (lx + rx) >> 1;
        push(x, lx, m, rx);
        if (l == lx && r == rx) {
            return tree[x].mx;
        }
        int s1 = mx(x + 1, lx, m, l, min(m, r));
        int s2 = mx(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r);
        return max(s1, s2);
    }
    void change(int x, int lx, int rx, int i, int v) {
        int m = (lx + rx) >> 1;
        push(x, lx, m, rx);
        if (lx == rx) {
            tree[x] = {v, 0};
            return;
        }
        if (i <= m) {
            change(x + 1, lx, m, i, v);
        } else {
            change(x + 2 * (m - lx + 1), m + 1, rx, i, v);
        }
        tree[x] = tree[x + 1].combine(tree[x + 2 * (m - lx + 1)]);
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    mons.assign(n, {});
    for (int i = 0; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        mons[i] = {a, b, c};
    }
    sort(mons.begin(), mons.end(), [](auto &l, auto &r) {
        return l[1] < r[1];
    });
    Segtree seg;
    seg.init(n);
    for (int i = 0; i < n; ++i) {
        cout << mons[i][0] << '\n';
        seg.add(0, 0, n - 1, i, n - 1, mons[i][0]);
        for (int i = 0; i < n; ++i) {
            cout << seg.mx(0, 0, n - 1, i, i) << ' ';
        }
        cout << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}