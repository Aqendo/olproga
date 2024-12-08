#include <bits/stdc++.h>
using namespace std;

struct Segtree {
    vector<int> tree;
    void init(int n, map<int, vector<int>> &a) {
        tree.assign(2 * n - 1, INT_MAX);
        build(a, 0, 0, n - 1);
    }
    void build(map<int, vector<int>> &a, int x, int lx, int rx) {
        if (lx == rx) {
            tree[x] = (a.find(lx) == a.end() || a[lx].empty()) ? INT_MAX : a[lx].back();
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, x + 1, lx, m);
        build(a, x + 2 * (m - lx + 1), m + 1, rx);
        tree[x] = max(tree[x + 1], tree[x + 2 * (m - lx + 1)]);
    }
    int get(int x, int lx, int rx, int l, int r) {
        if (l > r) return 0;
        if (l == lx && r == rx) return tree[x];
        int m = (lx + rx) >> 1;
        int s1 = get(x + 1, lx, m, l, min(m, r));
        int s2 = get(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r);
        return max(s1, s2);
    }
    void change(int x, int lx, int rx, int i, int v) {
        if (lx == rx) {
            tree[x] = v;
            return;
        }
        int m = (lx + rx) >> 1;
        if (i <= m) {
            change(x + 1, lx, m, i, v);
        } else {
            change(x + 2 * (m - lx + 1), m + 1, rx, i, v);
        }
        tree[x] = max(tree[x + 1], tree[x + 2 * (m - lx + 1)]);
    }
};

void solve() {
    int g;
    cin >> g;
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    map<int, vector<int>> occurences;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        occurences[a[i]].push_back(i);
    }
    for (auto &[u, v] : occurences) {
        reverse(v.begin(), v.end());
    }
    Segtree seg;
    seg.init(n + 1, occurences);
    map<int, vector<int>> pairs;
    int additions = 0;
    for (int l = 0; l < n; ++l) {
        int now_size = 1;
        int res = seg.get(0, 0, n, 1, now_size);
        while (res != INT_MAX) {
            while (res - l + 1 > now_size && res != INT_MAX) {
                now_size = res - l + 1;
                res = seg.get(0, 0, n, 1, now_size);
            }
            if (res == INT_MAX) {
                continue;
            }
            pairs[l].push_back(now_size);
            now_size++;
            res = seg.get(0, 0, n, 1, now_size);
        }
        occurences[a[l]].pop_back();
        if (occurences[a[l]].empty()) {
            seg.change(0, 0, n, a[l], INT_MAX);
        } else {
            seg.change(0, 0, n, a[l], occurences[a[l]].back());
        }
    }
    for (auto &[u, v] : pairs) {
        sort(v.begin(), v.end());
    }
    for (int i = 0; i < q; ++i) {
        int l, x;
        cin >> l >> x;
        l--;
        if (pairs.find(l) == pairs.end()) {
            cout << "-1 0\n";
            continue;
        }
        auto it = lower_bound(pairs[l].begin(), pairs[l].end(), x);
        if (it == pairs[l].end()) {
            cout << "-1 0\n";
            continue;
        }
        cout << *it << ' ' << pairs[l].end() - it << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}