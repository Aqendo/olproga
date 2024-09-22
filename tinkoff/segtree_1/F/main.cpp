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

struct Segtree {
    vector<int> tree;
    int n;
    Segtree(int n_) : n(n_), tree(4 * n_) {}
    void add(int x, int lx, int rx, int i, int v) {
        if (lx == rx) {
            tree[x] += v;
            return;
        }
        int m = (lx + rx) >> 1;
        if (i <= m) {
            add(x << 1, lx, m, i, v);
        } else {
            add(x << 1 | 1, m + 1, rx, i, v);
        }
        tree[x] = tree[x << 1] + tree[x << 1 | 1];
    }
    int get(int x, int lx, int rx, int l, int r) {
        if (l > r) return 0;
        if (l == lx && rx == r) return tree[x];
        int m = (lx + rx) >> 1;
        int s1 = get(x << 1, lx, m, l, min(m, r));
        int s2 = get(x << 1 | 1, m + 1, rx, max(m + 1, l), r);
        return s1 + s2;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> uni_only(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        uni_only[i] = a[i];
    }
    sort(uni_only.begin(), uni_only.end());
    uni_only.erase(unique(uni_only.begin(), uni_only.end()), uni_only.end());
    map<int, int> narr;
    for (int i = 0; i < uni_only.size(); ++i) {
        narr[uni_only[i]] = i;
    }
    int k = 3;
    vector dp(n, vector(k + 1, 0));
    for (int i = 0; i < n; ++i) {
        dp[i][1] = 1;
    }
    for (int kk = 1; kk <= k; ++kk) {
        Segtree seg(uni_only.size());
        for (int i = 0; i < n; ++i) {
            dp[i][kk] += seg.get(1, 0, seg.n, narr[a[i]] + 1, seg.n);
            seg.add(1, 0, seg.n, narr[a[i]], dp[i][kk - 1]);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += dp[i][k];
    }
    cout << ans;
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
