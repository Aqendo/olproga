#include "bits/stdc++.h"

#define int long long
using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
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
    void set(int x, int lx, int rx, int i, int v) {
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
    pair<int, int> get(int x, int lx, int rx, int k, int l, int r, int already) {
        if (l > r) return {-1, 0};
        if (lx == l && rx == r && gcd(tree[x], already) > k) {
            return {-1, gcd(tree[x], already)};
        }
        if (lx == rx) {
            return {lx, gcd(tree[x], already)};
        }
        pair<int, int> answer;
        int m = (lx + rx) >> 1;
        auto first = get(x << 1, lx, m, k, l, min(m, r), already);
        if (first.second != 0 && gcd(already, first.second) <= k) {
            answer = first;
        } else {
            answer = get(x << 1 | 1, m + 1, rx, k, max(m + 1, l), r, gcd(already, first.second));
        }
        return answer;
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
            int index, x;
            cin >> index >> x;
            index--;
            seg.set(1, 0, n - 1, index, x);
        } else {
            int k, from;
            cin >> k >> from;
            from--;
            pair<int, int> answer = seg.get(1, 0, n - 1, k, from, n - 1, 0);
            if (answer.first == -1) {
                cout << -1 << '\n';
            } else {
                cout << answer.first - from + 1 << '\n';
            }
            debug(answer);
        }
    }
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
