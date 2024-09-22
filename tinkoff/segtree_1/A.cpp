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
struct Node {
    int val, index;
};
struct Segtree {
    vector<Node> tree;
    int n;
    Segtree(vector<int>& a) : n(a.size()), tree(4 * a.size()) { build(a, 1, 0, n - 1); }
    Node combine(const Node& l, const Node& r) {
        if (l.val > r.val) return l;
        return r;
    }
    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx) {
            if (lx < n) {
                tree[x] = {a[lx], lx + 1};
            }
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, x << 1, lx, m);
        build(a, x << 1 | 1, m + 1, rx);
        tree[x] = combine(tree[x << 1], tree[x << 1 | 1]);
    }
    Node get(int x, int lx, int rx, int l, int r) {
        if (l > r) return {.val = LLONG_MIN};
        if (lx == l && rx == r) return tree[x];
        int m = (lx + rx) >> 1;
        Node s1 = get(x << 1, lx, m, l, min(m, r));
        Node s2 = get(x << 1 | 1, m + 1, rx, max(m + 1, l), r);
        return combine(s1, s2);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    Segtree seg(a);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        cout << seg.get(1, 0, n - 1, l - 1, r - 1).index << '\n';
    }
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
