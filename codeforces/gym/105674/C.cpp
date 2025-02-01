#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define int int64_t

template <typename T>
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int N = 1e5 + 78;

int h[N], ll[N], rr[N], edgeL[N], edgeR[N];

struct Segtree {
    int mx[2 * N], mn[2 * N], sum[2 * N], lazySet[N * 2];
    void init(int n, int *a) {
        memset(lazySet, -1, sizeof(lazySet));
        build(a, 0, 0, n - 1);
    }
    void build(int *a, int x, int lx, int rx) {
        if (lx == rx) {
            mx[x] = sum[x] = mn[x] = a[lx];
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, x + 1, lx, m);
        build(a, x + 2 * (m - lx + 1), m + 1, rx);
        sum[x] = sum[x + 1] + sum[x + 2 * (m - lx + 1)];
        mx[x] = max(mx[x + 1], mx[x + 2 * (m - lx + 1)]);
        mn[x] = min(mn[x + 1], mn[x + 2 * (m - lx + 1)]);
    }
    void push(int x, int lx, int m, int rx) {
        if (lazySet[x] == -1) return;
        if (lx == rx) {
            lazySet[x] = -1;
            return;
        };
        sum[x + 1] = (m - lx + 1) * lazySet[x];
        mx[x + 1] = lazySet[x];
        mn[x + 1] = lazySet[x];
        lazySet[x + 1] = lazySet[x];

        sum[x + 2 * (m - lx + 1)] = (rx - m) * lazySet[x];
        mx[x + 2 * (m - lx + 1)] = lazySet[x];
        mn[x + 2 * (m - lx + 1)] = lazySet[x];
        lazySet[x + 2 * (m - lx + 1)] = lazySet[x];

        lazySet[x] = -1;
    }
    void maxeq(int x, int lx, int rx, int l, int r, int v) {
        if (l > r || mn[x] >= v) return;
        int m = (lx + rx) >> 1;
        push(x, lx, m, rx);
        if (lx == rx) {
            mn[x] = mx[x] = max(mx[x], v);
            sum[x] = max(sum[x], v);
            return;
        }
        if (l == lx && r == rx) {
            if (mx[x] < v) {
                lazySet[x] = v;
                sum[x] = (rx - lx + 1) * v;
                mx[x] = v;
                mn[x] = v;
                return;
            }
        }
        maxeq(x + 1, lx, m, l, min(m, r), v);
        maxeq(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r, v);
        sum[x] = sum[x + 1] + sum[x + 2 * (m - lx + 1)];
        mx[x] = max(mx[x + 1], mx[x + 2 * (m - lx + 1)]);
        mn[x] = min(mn[x + 1], mn[x + 2 * (m - lx + 1)]);
    }
    int getsum(int x, int lx, int rx, int l, int r) {
        if (l > r) return 0;
        int m = (lx + rx) >> 1;
        push(x, lx, m, rx);
        if (l == lx && r == rx) return sum[x];
        int s1 = getsum(x + 1, lx, m, l, min(m, r));
        int s2 = getsum(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r);
        return s1 + s2;
    }
    int getmx(int x, int lx, int rx, int l, int r) {
        if (l > r) return INT_MIN;
        int m = (lx + rx) >> 1;
        push(x, lx, m, rx);
        if (l == lx && r == rx) return mx[x];
        int s1 = getmx(x + 1, lx, m, l, min(m, r));
        int s2 = getmx(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r);
        return max(s1, s2);
    }
};
struct SegtreeMXSUM {
    vector<pair<int, int>> mx;
    vector<int> sum;
    void init(int n) {
        mx.assign(2 * n - 1, {INT_MIN, INT_MIN});
        sum.assign(2 * n - 1, 0);
        build(0, 0, n - 1);
    }
    void build(int x, int lx, int rx) {
        if (lx == rx) {
            mx[x] = {h[lx], lx};
            sum[x] = h[lx];
            return;
        }
        int m = (lx + rx) >> 1;
        build(x + 1, lx, m);
        build(x + 2 * (m - lx + 1), m + 1, rx);
        mx[x] = max(mx[x + 1], mx[x + 2 * (m - lx + 1)]);
        sum[x] = sum[x + 1] + sum[x + 2 * (m - lx + 1)];
    }
    pair<int, int> getmx(int x, int lx, int rx, int l, int r) {
        if (l > r) return {INT_MIN, INT_MIN};
        if (l == lx && r == rx) return mx[x];
        int m = (lx + rx) >> 1;
        auto s1 = getmx(x + 1, lx, m, l, min(m, r));
        auto s2 = getmx(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r);
        return max(s1, s2);
    }
    int getsum(int x, int lx, int rx, int l, int r) {
        if (l > r) return 0;
        if (l == lx && r == rx) return sum[x];
        int m = (lx + rx) >> 1;
        auto s1 = getsum(x + 1, lx, m, l, min(m, r));
        auto s2 = getsum(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r);
        return s1 + s2;
    }
};
Segtree segl, segr;
SegtreeMXSUM segh;

int n;
void getrecalculated(int one, int second) {
    int from = edgeL[one], to = edgeR[second];
    auto [mxL, mxLindex] = segh.getmx(0, 0, n - 1, edgeL[one], edgeR[one]);
    auto [mxR, mxRindex] = segh.getmx(0, 0, n - 1, edgeL[second], edgeR[second]);

    segr.maxeq(0, 0, n - 1, edgeL[one], edgeR[one], mxR);
    segl.maxeq(0, 0, n - 1, edgeL[second], edgeR[second], mxL);
    int index = mxL > mxR ? mxLindex : mxRindex;
    int answer = 0;
    answer += segr.getsum(0, 0, n - 1, index + 1, to);
    answer += segl.getsum(0, 0, n - 1, from, index);
    answer -= segh.getsum(0, 0, n - 1, from, to);
    cout << answer << '\n';
    edgeL[second] = edgeL[one];
}
void solve() {
    cin >> n;
    oset<int> indicies;
    for (int i = 0; i < n; ++i) {
        indicies.insert(i);
    }
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
        ll[i] = rr[i] = h[i];
        edgeL[i] = edgeR[i] = i;
    }
    segl.init(n, ll);
    segr.init(n, rr);
    segh.init(n);
    for (int i = 0; i < n - 1; ++i) {
        int kj;
        cin >> kj;
        kj--;
        auto it = indicies.find_by_order(kj);
        getrecalculated(*it, *next(it));
        indicies.erase(it);
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}