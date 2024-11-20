#include <bits/stdc++.h>
using namespace std;
#define int int64_t
struct Segtree {
    vector<pair<int, int>> tree;
    vector<array<int, 3>> found;
    int n;
    Segtree(vector<int>& a) : n(a.size()), tree(4 * a.size(), {INT_MAX, -1}) { build(a, 1, 0, (int)a.size() - 1); }
    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx) {
            if (lx < (int)a.size()) {
                tree[x] = {a[lx], lx};
            }
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, x << 1, lx, m);
        build(a, x << 1 | 1, m + 1, rx);
        tree[x] = min(tree[x << 1], tree[x << 1 | 1]);
    }
    void change(int x, int lx, int rx, int i, int v) {
        if (lx == rx) {
            tree[x].first = v;
            return;
        }
        int m = (lx + rx) >> 1;
        if (i <= m) {
            change(x << 1, lx, m, i, v);
        } else {
            change(x << 1 | 1, m + 1, rx, i, v);
        }
        tree[x] = min(tree[x << 1], tree[x << 1 | 1]);
    }
    pair<int, int> get_lower_than_full(int x, int lx, int rx, int v) {
        if (lx == rx) {
            return tree[x];
        }
        int m = (lx + rx) >> 1;
        if (tree[x << 1].first <= v) {
            return get_lower_than_full(x << 1, lx, m, v);
        } else if (tree[x << 1 | 1].first <= v) {
            return get_lower_than_full(x << 1 | 1, m + 1, rx, v);
        } else {
            return {INT_MAX, -1};
        }
    }
    void get_index_lower__(int x, int lx, int rx, int l, int r, int v, int first = true) {
        if (l > r) return;
        if (l == lx && r == rx) {
            found.push_back({x, lx, rx});
            return;
        }
        int m = (lx + rx) >> 1;
        get_index_lower__(x << 1, lx, m, l, min(m, r), v);
        get_index_lower__(x << 1 | 1, m + 1, rx, max(m + 1, l), r, v);
    }
    int get_index_lower(int l, int r, int v) {
        found.clear();
        get_index_lower__(1, 0, n - 1, l, r, v);
        for (auto& [x, lx, rx] : found) {
            pair<int, int> answer = get_lower_than_full(x, lx, rx, v);
            if (answer.first <= v) {
                return answer.second;
            }
        }
        return -1;
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
    int days = 0;
    int power = 1;
    while (true) {
        int now = seg.get_index_lower(0, n - 1, power);
        if (now == -1) {
            break;
        }
        days++;
        while (now != -1) {
            power++;
            seg.change(1, 0, n - 1, now, INT_MAX);
            now = seg.get_index_lower(now + 1, n - 1, power);
        }
    }
    if (power != n + 1) {
        cout << -1 << '\n';
    } else {
        cout << days << '\n';
    }
}
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) solve();
}