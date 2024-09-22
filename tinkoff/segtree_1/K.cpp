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
    int full_pairs = 0;
    int opened = 0, closed = 0;
};

struct Segtree {
    vector<Node> tree;
    int n;
    Segtree(string& a) : tree(4 * a.size()), n(a.size()) { build(a, 1, 0, n - 1); }

    Node combine(const Node& l, const Node& r) {
        Node res = {0};
        res.full_pairs = l.full_pairs + r.full_pairs;
        int brought = min(l.opened, r.closed);
        res.opened = l.opened + r.opened - brought;
        res.closed = l.closed + r.closed - brought;
        res.full_pairs += brought;
        return res;
    }

    void build(const string& s, int x, int lx, int rx) {
        if (lx == rx) {
            tree[x] = {.full_pairs = 0, .opened = s[lx] == '(', .closed = s[lx] == ')'};
            return;
        }
        int m = (lx + rx) >> 1;
        build(s, x << 1, lx, m);
        build(s, x << 1 | 1, m + 1, rx);
        tree[x] = combine(tree[x << 1], tree[x << 1 | 1]);
    }
    Node get(int x, int lx, int rx, int l, int r) {
        if (l > r) return {0, 0, 0};
        if (lx == l && rx == r) return tree[x];
        int m = (lx + rx) >> 1;
        Node s1 = get(x << 1, lx, m, l, min(m, r));
        Node s2 = get(x << 1 | 1, m + 1, rx, max(m + 1, l), r);
        return combine(s1, s2);
    }
};

void solve() {
    string s;
    cin >> s;
    Segtree seg(s);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        cout << seg.get(1, 0, seg.n - 1, l, r).full_pairs * 2 << '\n';
    }
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
