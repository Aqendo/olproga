#include <bits/stdc++.h>
using namespace std;
#define int int64_t

struct Monster {
    int i, s, u;
    bool operator<(const Monster &r) const {
        return i < r.i;
    }
};

int n, k;

struct MST {
    vector<vector<Monster>> tree;
    vector<vector<int>> pref;
    void init(vector<Monster> &a) {
        tree.assign(2 * n - 1, {});
        pref.assign(2 * n - 1, {});
        build(a, 0, 0, a.size() - 1);
    }
    void build(vector<Monster> &a, int x, int lx, int rx) {
        if (lx == rx) {
            tree[x] = {a[lx]};
            pref[x] = {a[lx].u};
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, x + 1, lx, m);
        build(a, x + 2 * (m - lx + 1), m + 1, rx);
        tree[x].resize(tree[x + 1].size() + tree[x + 2 * (m - lx + 1)].size());
        merge(tree[x + 1].begin(), tree[x + 1].end(), tree[x + 2 * (m - lx + 1)].begin(), tree[x + 2 * (m - lx + 1)].end(), tree[x].begin());
        pref[x].resize(tree[x].size());
        for (int i = 0; i < (int)tree[x].size(); ++i) {
            if (i != 0) pref[x][i] = pref[x][i - 1];
            pref[x][i] += tree[x][i].u;
        }
    }
    pair<int, int> get(int x, int lx, int rx, int l, int r, int leq) {
        if (l > r) return {0, 0};
        if (l == lx && r == rx) {
            auto it = upper_bound(tree[x].begin(), tree[x].end(), Monster{.i = leq});
            if (it == tree[x].begin()) return {0, 0};
            int index = it - 1 - tree[x].begin();
            return {index + 1, pref[x][index]};
        }
        int m = (lx + rx) >> 1;
        pair<int, int> s1 = get(x + 1, lx, m, l, min(m, r), leq);
        pair<int, int> s2 = get(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r, leq);
        return {s1.first + s2.first, s1.second + s2.second};
    }
};

vector<Monster> m;
MST mst;
clock_t ST;
double TL() {
    return (double)(clock() - ST) / CLOCKS_PER_SEC;
}
bool f(int X, int r) {
    int addition = 0;
    int old_sz = 0;
    while (true) {
        auto [sz, new_addition] = mst.get(0, 0, n - 1, 0, r, X + addition);
        if (sz >= k) return true;
        if (addition == new_addition && sz == old_sz) break;
        addition = new_addition;
        old_sz = sz;
    }
    return false;
}

int get(int Y) {
    int l = 0, r = n;
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        if (m[mid].s <= Y) {
            l = mid;
        } else {
            r = mid;
        }
    }
    if (m[l].s > Y) return -1;
    int to = l;
    // [0, l]
    l = -1, r = 1e9;
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        if (f(mid, to)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    if (f(r, to)) return r;
    return -1;
}

void solve() {
    cin >> n >> k;
    m.resize(n);
    vector<int> xs(n);
    for (int i = 0; i < n; ++i) {
        cin >> m[i].i >> m[i].s >> m[i].u;
        xs[i] = m[i].s;
    }
    sort(m.begin(), m.end(), [](const Monster &l, const Monster &r) {
        if (l.s != r.s) return l.s < r.s;
        return l.i < r.i;
    });
    mst.init(m);
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    int answer = INT_MAX;
    int l = 0, r = xs.size();
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        if (get(xs[mid]) == -1) {
            l = mid;
        } else {
            r = mid;
        }
    }
    int from = max<int>(0, r - 1);
    l = r;
    r = xs.size();
    while (r - l > 3) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        int f1 = get(xs[m1]);
        if (f1 == -1) f1 = 1e9;
        int f2 = get(xs[m2]);
        if (f2 == -1) f2 = 1e9;
        if (f1 == 1e9) {
            l = m1;
            continue;
        }
        answer = min(answer, xs[m1] + f1);
        answer = min(answer, xs[m2] + f2);
        if (xs[m1] + f1 > xs[m2] + f2) {
            l = m1;
        } else {
            r = m2;
        }
    }
    for (int i = max<int>(from, l - 2 * (int(2e8) / n)); i <= min(n - 1, r + 3 * (int(2e8) / n)); ++i) {
        int res = get(xs[i]);
        if (res != -1) {
            answer = min(answer, xs[i] + res);
        }
        if (i % 30 == 0)
            if (TL() > 1.4) {
                cout << answer << '\n';
                return;
            }
    }
    cout << answer << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}