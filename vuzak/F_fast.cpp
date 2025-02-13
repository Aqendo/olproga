#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 5e5 + 78;

int a[N];
struct Node {
    int mx, mn;
};
struct {
    vector<Node> tree;
    void init(int n) {
        tree.assign(2 * n - 1, {INT_MIN, INT_MAX});
        build(0, 0, n - 1);
    }
    void build(int x, int lx, int rx) {
        if (lx == rx) {
            tree[x] = {a[lx] + lx, a[lx] + lx};
            return;
        }
        int m = (lx + rx) >> 1;
        build(x + 1, lx, m);
        build(x + 2 * (m - lx + 1), m + 1, rx);
        tree[x] = combine(tree[x + 1], tree[x + 2 * (m - lx + 1)]);
    }
    Node combine(const auto& l, const auto& r) {
        return {
            max(l.mx, r.mx),
            min(l.mn, r.mn)};
    }
    pair<int, int> get(int x, int lx, int rx, int l, int r, int leq) {
        if (l > r) return {-2, 0};
        if (l == lx && r == rx) {
            if (lx == rx) {
                if (tree[x].mx <= leq) return {lx, 0};
                return {-1, 1};
            }
            int m = (lx + rx) >> 1;
            if (tree[x + 1].mx <= leq) {
                if (tree[x + 2 * (m - lx + 1)].mx <= leq) {
                    return {rx, 0};
                }
                if (tree[x + 2 * (m - lx + 1)].mn <= leq) {
                    pair<int, int> s2 = get(x + 2 * (m - lx + 1), m + 1, rx, max(l, m + 1), r, leq);
                    return {max(m, s2.first), s2.second};
                }
                return {m, 1};
            } else if (tree[x + 1].mn <= leq) {
                return get(x + 1, lx, m, l, min(m, r), leq);
            }
            return {-1, 1};
        }
        int m = (lx + rx) >> 1;
        pair<int, int> s1 = get(x + 1, lx, m, l, min(m, r), leq);
        if (s1.second > 0) return s1;
        pair<int, int> s2 = get(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r, leq);
        return {max(s1.first, s2.first), max(s1.second, s2.second)};
    }
} seg;

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        // cout << a[i] + i << " \n"[i == n - 1];
    }
    seg.init(n);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, x;
        cin >> l >> x;
        auto [res, was] = seg.get(0, 0, n - 1, l - 1, n - 1, x + l - 1);
        if (res == -1) {
            cout << 0 << '\n';
            continue;
        }
        cout << res - (l - 1) + 1 << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
