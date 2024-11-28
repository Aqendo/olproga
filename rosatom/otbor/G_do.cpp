#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("popcnt,lzcnt,avx2")
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;
int min(int a, int b) {
    return a < b ? a : b;
}
struct Segtree {
    vector<int> tree;
    void init(const vector<pair<int, int>>& arr) {
        tree.assign(2 * arr.size() - 1, INT_MAX);
        build(arr, 0, 0, arr.size() - 1);
    }
    void build(const vector<pair<int, int>>& arr, int x, int lx, int rx) {
        if (lx == rx) {
            tree[x] = arr[lx].second;
            return;
        }
        int m = (lx + rx) >> 1;
        build(arr, x + 1, lx, m);
        build(arr, x + 2 * (m - lx + 1), m + 1, rx);
        tree[x] = min(tree[x + 1], tree[x + 2 * (m - lx + 1)]);
    }
    int get_min(int x, int lx, int rx, int l, int r) {
        if (lx == l && rx == r) return tree[x];
        int m = (lx + rx) >> 1;
        int a1 = (l <= min(m, r) ? get_min(x + 1, lx, m, l, min(m, r)) : (int)1e9 + 4);
        int a2 = (max(m + 1, l) <= r ? get_min(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r) : (int)1e9 + 4);
        return min(a1, a2);
    }
};
Segtree spb, spc;
int n;
long long x;
long long answer = 1e18;
bool check(long long max_delta, const vector<pair<int, int>>& a, const vector<pair<int, int>>& b, const vector<pair<int, int>>& c) {
    int lb = 0, rb = -1;
    int lc = 0, rc = -1;
    for (int i = 0; i < n; ++i) {
        while ((int)b.size() > rb + 1 && b[rb + 1].first <= a[i].first) {
            rb++;
        }
        while ((int)b.size() > lb && b[lb].first < a[i].first - max_delta) {
            lb++;
        }
        while ((int)c.size() > rc + 1 && c[rc + 1].first <= a[i].first) {
            rc++;
        }
        while ((int)c.size() > lc && c[lc].first < a[i].first - max_delta) {
            lc++;
        }
        int a1 = spb.get_min(0, 0, n - 1, lb, rb);
        int a2 = spc.get_min(0, 0, n - 1, lc, rc);
        if (0ll + a[i].second + a1 + a2 <= x) {
            answer = min(answer, max_delta);
            return true;
        }
    }
    return false;
}
void solve(const vector<pair<int, int>>& a, const vector<pair<int, int>>& b, const vector<pair<int, int>>& c) {
    spb.init(b);
    spc.init(c);
    long long l = -1, r = 4e9;
    while (r - l > 1) {
        long long mid = (l + r) >> 1;
        if (check(mid, a, b, c)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    check(r, a, b, c);
}

void solve() {
    cin >> n >> x;
    vector<pair<int, int>> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
    }
    for (int i = 0; i < n; ++i) {
        cin >> a[i].second;
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i].first;
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i].second;
    }
    for (int i = 0; i < n; ++i) {
        cin >> c[i].first;
    }
    for (int i = 0; i < n; ++i) {
        cin >> c[i].second;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());
    solve(a, b, c);
    solve(b, a, c);
    solve(c, b, a);
    cout << (answer == 1e18 ? -1 : answer) << '\n';
};

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
