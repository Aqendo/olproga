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
    vector<vector<int>> tree;
    int n;
    Segtree(vector<int>& a) : tree(4 * a.size()), n(a.size()) { build(a, 1, 0, n - 1); }
    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx) {
            tree[x] = {a[lx]};
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, x << 1, lx, m);
        build(a, x << 1 | 1, m + 1, rx);
        merge(tree[x << 1].begin(), tree[x << 1].end(), tree[x << 1 | 1].begin(), tree[x << 1 | 1].end(), back_inserter(tree[x]));
    }
    int get(int x, int lx, int rx, int l, int r, int lower_than) {
        if (l > r) return 0;
        if (lx == l && rx == r) {
            return upper_bound(tree[x].begin(), tree[x].end(), lower_than) - tree[x].begin();
        }
        int m = (lx + rx) >> 1;
        int s1 = get(x << 1, lx, m, l, min(m, r), lower_than);
        int s2 = get(x << 1 | 1, m + 1, rx, max(m + 1, l), r, lower_than);
        return s1 + s2;
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
        int l, r, from, to;
        cin >> l >> r >> from >> to;
        l--;
        r--;
        cout << seg.get(1, 0, n - 1, l, r, to) - seg.get(1, 0, n - 1, l, r, from - 1) << '\n';
    }
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
