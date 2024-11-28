#include <bits/stdc++.h>
using namespace std;

struct Segtree {
    vector<int> tree;
    Segtree(vector<int>& a) : tree(2 * a.size() - 1) { build(a, 0, 0, (int)a.size() - 1); }
    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx) {
            tree[x] = a[lx];
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, x + 1, lx, m);
        build(a, x + 2 * (m - lx + 1), m + 1, rx);
        tree[x] = max(tree[x + 1], tree[x + 2 * (m - lx + 1)]);
    }
    void set(int x, int lx, int rx, int i, int v) {
        if (lx == rx) {
            tree[x] = v;
            return;
        }
        int m = (lx + rx) >> 1;
        if (i <= m) {
            set(x + 1, lx, m, i, v);
        } else {
            set(x + 2 * (m - lx + 1), m + 1, rx, i, v);
        }
        tree[x] = max(tree[x + 1], tree[x + 2 * (m - lx + 1)]);
    }
    pair<int, int> get(int x, int lx, int rx, int l, int r, int bigeq_than) {
        int m = (lx + rx) >> 1;
        // cout << l << ' ' << r << ' ' << tree[x] << ' ' << tree[x + 2 * (m - lx + 1)] << endl;
        if (l > r) return {INT_MIN, INT_MIN};
        if (l == lx && r == rx) {
            if (lx == rx) {
                if (tree[x] >= bigeq_than) {
                    return {tree[x], lx};
                }
                return {INT_MIN, INT_MIN};
            }
            // cout << "trees: " << tree[x + 1] << ' ' << tree[x + 2 * (m - lx + 1)] << '\n';
            if (tree[x + 1] >= bigeq_than) {
                return get(x + 1, lx, m, l, min(m, r), bigeq_than);
            } else if (tree[x + 2 * (m - lx + 1)] >= bigeq_than) {
                return get(x + 2 * (m - lx + 1), m + 1, rx, max(l, m + 1), r, bigeq_than);
            }
            return {INT_MIN, INT_MIN};
        }
        pair<int, int> fans = get(x + 1, lx, m, l, min(m, r), bigeq_than);
        if (fans.first >= bigeq_than) {
            return fans;
        }
        return get(x + 2 * (m - lx + 1), m + 1, rx, max(l, m + 1), r, bigeq_than);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    Segtree seg(a);
    for (int i = 0; i < m; ++i) {
        int move, index, x;
        cin >> move >> index >> x;
        if (move == 0) {
            // set
            seg.set(0, 0, n - 1, index - 1, x);
        } else {
            pair<int, int> answer = seg.get(0, 0, n - 1, index - 1, n - 1, x);
            if (answer.first >= x) {
                cout << answer.second + 1 << '\n';
            } else {
                cout << -1 << '\n';
            }
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
