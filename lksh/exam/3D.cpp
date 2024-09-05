// #pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define int int64_t
using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#else
#define debug(...)
#endif

int cnt = 0;
int mn_len = INT_MAX;

struct Segtree {
    vector<long long> tree;
    int n;

    Segtree(vector<int>& a) : tree(4 * a.size()), n(a.size()) {
        build(a, 1, 0, (int)a.size() - 1);
    }

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

    int cnt = 0;

    int just_get(int x, int lx, int rx, int l, int r) {
        if (l > r) return 0;
        if (lx == l && rx == r) return tree[x];
        int m = (lx + rx) >> 1;
        int s1 = just_get(x << 1, lx, m, l, min(m, r));
        int s2 = just_get(x << 1 | 1, m + 1, rx, max(l, m + 1), r);
        return gcd(s1, s2);
    }

    int get(int x, int lx, int rx, int l, int r, int k, int already = 0) {
        if (l > r) return 0;
        // debug(x, lx, rx, l, r, k, already, tree[x]);
        if (gcd(already, tree[x]) <= k) {
            mn_len = min(mn_len, rx);
        } else {
            return tree[x];
        }
        if (lx == rx) return tree[x];
        int m = (lx + rx) >> 1;
        int now = just_get(x << 1, lx, m, l, min(r, m));
        get(x << 1, lx, m, l, min(r, m), k, already);
        if (now <= k && now != 0) return 0;
        return gcd(now, get(x << 1 | 1, m + 1, rx, max(l, m + 1), rx, k,
                            gcd(now, already)));
    }

    /*
    int64_t get_full_count(int64_t x, int64_t lx, int64_t rx, int64_t l,
                           int64_t r) {
        if (l > r) return 0;
        if (lx == l && rx == r) return tree[x];
        int64_t m = (lx + rx) >> 1;
        int64_t s1 = get_full_count(x << 1, lx, m, l, min(m, r));
        int64_t s2 = get_full_count(x << 1 | 1, m + 1, rx, max(l, m + 1), r);
        return s1 + s2;
    }*/

    void set(int x, int lx, int rx, int i, long long v) {
        if (lx == rx) {
            tree[x] = v;
            return;
        }
        int m = (lx + rx) >> 1;
        if (i <= m) {
            set(x << 1, lx, m, i, v);
        } else {
            set(x << 1 | 1, m + 1, rx, i, v);
        }
        tree[x] = gcd(tree[x << 1], tree[x << 1 | 1]);
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
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int move;
        cin >> move;
        if (move == 1) {
            long long start, k;
            cin >> start >> k;
            mn_len = INT_MAX;
            seg.get(1, 0, n - 1, start - 1, n - 1, k);
            if (mn_len == INT_MAX) {
                cout << "0\n";
            } else {
                cout << mn_len - start + 2 << '\n';
            }
        } else {
            int i_, x;
            cin >> i_ >> x;
            seg.set(1, 0, n - 1, i_ - 1, x);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}