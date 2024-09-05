#pragma GCC optimize("O3")
#include "bits/stdc++.h"

using namespace std;
#define int long long
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#else
#define debug(...)
#endif

struct Segtree {
    vector<int> tree;
    int n;
    Segtree(vector<int>& a) : tree(4 * a.size()), n(a.size()) { build(a, 1, 0, n - 1); }
    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx) {
            if (lx < n) {
                tree[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, x << 1, lx, m);
        build(a, x << 1 | 1, m + 1, rx);
        tree[x] = gcd(tree[x << 1], tree[x << 1 | 1]);
    }
    int get(int x, int lx, int rx, int l, int r) {
        if (l > r) return 0;
        if (lx == l && rx == r) {
            return tree[x];
        }
        int m = (lx + rx) >> 1;
        int s1 = get(x << 1, lx, m, l, min(m, r));
        int s2 = get(x << 1 | 1, m + 1, rx, max(m + 1, l), r);
        return gcd(s1, s2);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    vector<int> razn_a(n), razn_b(n);
    for (int i = 1; i < n; ++i) {
        razn_a[i - 1] = abs(a[i] - a[i - 1]);
    }
    for (int i = 1; i < n; ++i) {
        razn_b[i - 1] = abs(b[i] - b[i - 1]);
    }
    debug(razn_a, razn_b);
    Segtree razn_a_tree(razn_a), razn_b_tree(razn_b);
    for (int i = 0; i < q; ++i) {
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        int res_a = razn_a_tree.get(1, 0, n - 1, x1 - 1, x2 - 2);
        int res_b = razn_b_tree.get(1, 0, n - 1, y1 - 1, y2 - 2);
        debug(res_a, res_b);
        cout << gcd(res_a, gcd(res_b, a[x1 - 1] + b[y1 - 1])) << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
