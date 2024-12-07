#include <bits/stdc++.h>
using namespace std;

struct MST {
    vector<map<int, int>> tree;
    MST(vector<int>& a) : tree(2 * a.size() - 1) { build(a, 0, 0, a.size() - 1); }
    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx) {
            tree[x] = {{a[lx], 1}};
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, x + 1, lx, m);
        build(a, x + 2 * (m - lx + 1), m + 1, rx);
        tree[x] = tree[x + 1];
        for (auto& [u, v] : tree[x + 2 * (m - lx + 1)]) {
            tree[x][u] += v;
        }
    }
    int get(int x, int lx, int rx, int l, int r, int toget) {
        if (l > r) return 0;
        if (l == lx && r == rx) {
            return tree[x][toget];
        }
        int m = (lx + rx) >> 1;
        int s1 = get(x + 1, lx, m, l, min(m, r), toget);
        int s2 = get(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r, toget);
        return s1 + s2;
    }
};
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);
    MST segtree(a);
    cout << segtree.get(0, 0, n - 1, 0, n - 2, 3);
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}