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

struct Arifm {
    int a1, k;
};

struct Node {
    int sum;
    int len;
    int index;
};
int sum(const Arifm& arifm, const int len) {
    return (2 * arifm.a1 + arifm.k * (len - 1)) * len / 2;
}
struct Segtree {
    vector<Node> tree;
    vector<int> lazy_add;
    vector<Arifm> lazy_arifm;
    int n;
    Segtree(int n_) : n(n_), tree(4 * n_), lazy_add(4 * n_), lazy_arifm(4 * n_) { build(1, 0, n - 1); }
    void build(int x, int lx, int rx) {
        if (lx == rx) {
            if (lx < n) {
                tree[x] = {0, 1, lx};
            }
            return;
        }
        int m = (lx + rx) >> 1;
        build(x << 1, lx, m);
        build(x << 1 | 1, m + 1, rx);
        tree[x] = combine(tree[x << 1], tree[x << 1 | 1]);
    }
    Node combine(const Node& l, const Node& r, int lazy_ = 0, Arifm arifm_ = {0, 0}, int lx = -69) const {
        // printf("l(%lld[%lld]], r(%lld[%lld]], lazy=%lld, arifm_=(%lld;%lld)\n", l.sum, l.len, r.sum, r.len, lazy_, arifm_.a1, arifm_.k);
        Node res = {l.sum + r.sum, l.len + r.len};
        res.index = l.len > 0 ? l.index : r.index;
        res.sum += lazy_ * res.len;
        if (arifm_.a1 != 0 || arifm_.k != 0) {
            if (lx == -69) {
                // printf("len=%lld, a1=%lld, k=%lld, sum=%lld\n", res.len, arifm_.a1, arifm_.k, sum(arifm_, res.len));
                res.sum += sum(arifm_, res.len);
            } else {
                arifm_.a1 += (res.index - lx) * arifm_.k;
                // printf("1-len=%lld, a1_new=%lld, k=%lld, sum=%lld\n", res.len, arifm_.a1, arifm_.k, sum(arifm_, res.len));
                res.sum += sum(arifm_, res.len);
            }
        }
        // printf("res(%lld[%lld])\n", res.sum, res.len);
        return res;
    }
    void add(int x, int lx, int rx, int l, int r, int a1, int k) {
        if (l > r) return;
        if (l == lx && r == rx) {
            lazy_arifm[x].a1 += a1;
            lazy_arifm[x].k += k;
            if (lx != rx) {
                // printf("combine add1\n");
                tree[x] = combine(tree[x << 1], tree[x << 1 | 1], lazy_add[x], lazy_arifm[x]);
            } else {
                // printf("combine add2\n");
                tree[x] = combine({0, 1}, {0, 0}, lazy_add[x], lazy_arifm[x]);
            }
            return;
        }
        int m = (lx + rx) >> 1;
        add(x << 1, lx, m, l, min(m, r), a1, k);
        // printf("l=%lld, a1=%lld, m+1=%lld, res_a1=%lld\n", l, a1, m + 1, a1 + max<int>(0, m + 1 - l) * k);
        add(x << 1 | 1, m + 1, rx, max(m + 1, l), r, a1 + max<int>(0, m + 1 - l) * k, k);
        // printf("combine add2\n");
        tree[x] = combine(tree[x << 1], tree[x << 1 | 1], lazy_add[x], lazy_arifm[x]);
    }

    Node get(int x, int lx, int rx, int l, int r) const {
        // printf("[%lld;%lld]\n", lx, rx);
        if (l > r) return {0, 0, 0};
        if (l == lx && rx == r) return combine(tree[x], {0, 0}, 0, {0, 0});
        int m = (lx + rx) >> 1;
        Node s1 = get(x << 1, lx, m, l, min(m, r));
        Node s2 = get(x << 1 | 1, m + 1, rx, max(m + 1, l), r);
        // printf("x=%lld, lx=%lld, rx=%lld, combine get\n", x, lx, rx);
        return combine(s1, s2, lazy_add[x], lazy_arifm[x], lx);
    }
};

void print(const Segtree& seg) {
    for (int i = 0; i < seg.n; ++i) {
        cout << seg.get(1, 0, seg.n - 1, i, i).sum << ' ';
    }
    cout << '\n';
}

void solve() {
    int n, m;
    cin >> n >> m;
    Segtree seg(n);
    for (int ii = 0; ii < m; ++ii) {
        char move;
        cin >> move;
        if (move == '?') {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            cout << seg.get(1, 0, n - 1, l, r).sum << '\n';
        } else if (move == 'R') {
            // nashestviye
            int i, q;
            cin >> i >> q;
            i--;
            int lx = max<int>(0, i - q + 1);
            int rx = min(n - 1, i + q - 1);
            seg.add(1, 0, n - 1, lx, i, q - (i - lx), 1);
            seg.add(1, 0, n - 1, i + 1, rx, q - 1, -1);
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            l--;
            r--;
            seg.add(1, 0, n - 1, l, r, -x, 0);
        }
    }
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
