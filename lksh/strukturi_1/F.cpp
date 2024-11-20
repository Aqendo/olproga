#include <bits/stdc++.h>

using namespace std;

struct Events {
    vector<int64_t> opens;
    vector<int64_t> closes;
};
const int64_t INF = 1e18;
struct Segtree {
    vector<int64_t> tree;
    int64_t n;
    Segtree(int64_t nn) : tree(4 * nn, 1), n(nn) {}
    Segtree(int64_t nn, vector<int64_t>& a) : tree(4 * nn, 1), n(nn) { build(a, 1, 0, n - 1); }
    void build(vector<int64_t>& a, int64_t x, int64_t lx, int64_t rx) {
        if (lx == rx) {
            if (lx < n) {
                tree[x] = a[lx];
            }
            return;
        }
        int64_t m = (lx + rx) >> 1;
        build(a, x << 1, lx, m);
        build(a, x << 1 | 1, m + 1, rx);
        tree[x] = min(tree[x << 1], tree[x << 1 | 1]);
    }
    int64_t get(int64_t x, int64_t lx, int64_t rx, int64_t l, int64_t r) {
        if (l > r) {
            return INF;
        }
        if (lx == l && rx == r) {
            return tree[x];
        }
        int64_t m = (lx + rx) >> 1;
        int64_t s1 = get(x << 1, lx, m, l, min(m, r));
        int64_t s2 = get(x << 1 | 1, m + 1, rx, max(l, m + 1), r);
        return min(s1, s2);
    }
};
void solve() {
    int64_t n, m;
    cin >> n >> m;
    vector<int64_t> values(n);
    vector<Events> events(n + 1);
    vector<array<int64_t, 3>> event_list(m);
    multiset<int64_t> now;
    for (int64_t i = 0; i < m; ++i) {
        int64_t a, b, k;
        cin >> a >> b >> k;
        event_list[i] = {a, b, k};
        events[a].opens.push_back(k);
        events[b].closes.push_back(k);
    }
    for (int64_t i = 1; i <= n; ++i) {
        for (int64_t j : events[i].opens) {
            now.insert(j);
        }
        if (!now.empty()) {
            values[i - 1] = *now.rbegin();
        } else {
            values[i - 1] = 1e9;
        }
        for (int64_t j : events[i].closes) {
            now.extract(j);
        }
    }
    Segtree seg(n, values);
    for (auto& [a, b, k] : event_list) {
        if (seg.get(1, 0, n - 1, a - 1, b - 1) != k) {
            cout << "inconsistent\n";
            return;
        }
    }
    cout << "consistent\n";
    for (int64_t i : values) {
        cout << i << ' ';
    }
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}