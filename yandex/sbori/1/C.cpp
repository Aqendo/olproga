#include <bits/stdc++.h>
using namespace std;
#define int int64_t

struct Node {
    int cnt_odd, podd, peven, sodd, seven, s;
    Node combine(const Node &r) {
        if (cnt_odd == -1) return r;
        if (r.cnt_odd == -1) return *this;
        return Node{
            .cnt_odd = cnt_odd + r.cnt_odd + (sodd * r.peven) + (seven * r.podd) + (s % 2 != 0 ? r.peven : r.podd) + (r.s % 2 != 0 ? seven : sodd) + ((s + r.s) % 2 != 0),
            .podd = podd + (s % 2 == 0 ? r.podd : r.peven + 1),
            .peven = peven + (s % 2 == 0 ? r.peven + 1 : r.podd),
            .sodd = r.sodd + (r.s % 2 == 0 ? sodd : seven + 1),
            .seven = r.seven + (r.s % 2 == 0 ? seven + 1 : sodd),
            .s = s + r.s};
    }
};

struct Segtree {
    vector<Node> tree;
    void init(vector<int> &arr, int bit) {
        tree.assign(2 * arr.size() - 1, {});
        build(arr, 0, 0, arr.size() - 1, bit);
    }
    void build(vector<int> &arr, int x, int lx, int rx, int bit) {
        if (lx == rx) {
            int t = arr[lx] >> bit & 1;
            tree[x] = {
                .cnt_odd = t != 0,
                .podd = 0,
                .peven = 0,
                .sodd = 0,
                .seven = 0,
                .s = t};
            // cout << x << ' ' << lx << ' ' << rx << ": " << tree[x].cnt_odd << ' ' << tree[x].s << ' ' << endl;
            return;
        }
        int m = (lx + rx) >> 1;
        build(arr, x + 1, lx, m, bit);
        build(arr, x + 2 * (m - lx + 1), m + 1, rx, bit);
        tree[x] = tree[x + 1].combine(tree[x + 2 * (m - lx + 1)]);
        // cout << x << ' ' << lx << ' ' << rx << ": " << tree[x].cnt_odd << ' ' << tree[x].s << ' ' << endl;
    }
    Node get(int x, int lx, int rx, int l, int r) {
        if (l > r) {
            return Node{
                .cnt_odd = -1};
        }
        if (l == lx && r == rx) return tree[x];
        int m = (lx + rx) >> 1;
        Node s1 = get(x + 1, lx, m, l, min(m, r));
        Node s2 = get(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r);
        return s1.combine(s2);
    }
    void set(int x, int lx, int rx, int i, int v, int bit) {
        if (lx == rx) {
            int t = v >> bit & 1;
            tree[x] = {
                .cnt_odd = t != 0,
                .podd = 0,
                .peven = 0,
                .sodd = 0,
                .seven = 0,
                .s = t};
            return;
        }
        int m = (lx + rx) >> 1;
        if (i <= m) {
            set(x + 1, lx, m, i, v, bit);
        } else {
            set(x + 2 * (m - lx + 1), m + 1, rx, i, v, bit);
        }
        tree[x] = tree[x + 1].combine(tree[x + 2 * (m - lx + 1)]);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<Segtree> bits(30);
    for (int i = 0; i < 30; ++i) {
        bits[i].init(a, i);
    }
    for (int i = 0; i < q; ++i) {
        int move;
        cin >> move;
        if (move == 1) {
            int index, x;
            cin >> index >> x;
            for (int bit = 0; bit < 30; ++bit) {
                bits[bit].set(0, 0, n - 1, index - 1, x, bit);
            }
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            int s = 0;
            int mult = 1;
            for (int bit = 0; bit < 30; ++bit) {
                Node res = bits[bit].get(0, 0, n - 1, l, r);
                // cout << "ODD: " << res.cnt_odd << '\n';
                s += mult * res.cnt_odd;
                mult <<= 1;
            }
            cout << s << '\n';
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}