#include <bits/stdc++.h>
using namespace std;
#define int int64_t

struct Node {
    int mn;
    int lazy = 0;
    void combine(Node &l, Node &r) {
        mn = min(l.mn, r.mn);
    }
};

vector<int> a, b;
struct Segtree {
    vector<Node> tree;
    void init(vector<int> &indicies) {
        tree.assign(2 * indicies.size() - 1, {});
        build(indicies, 0, 0, indicies.size() - 1);
    }
    void build(vector<int> &inds, int x, int lx, int rx) {
        if (lx == rx) {
            tree[x].mn = b[lx];
            return;
        }
        int m = (lx + rx) >> 1;
        build(inds, x + 1, lx, m);
        build(inds, x + 2 * (m - lx + 1), m + 1, rx);
        tree[x].combine(tree[x + 1], tree[x + 2 * (m - lx + 1)]);
    }
    void add(int x, int lx, int rx, int l, int r, int remove) {
        if (l > r) return;
        int m = (lx + rx) >> 1;
        push(x, lx, m, rx);
        if (l == lx && r == rx) {
            tree[x].mn -= remove;
            tree[x].lazy += remove;
            return;
        }
        add(x + 1, lx, m, l, min(m, r), remove);
        add(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r, remove);
        tree[x].combine(tree[x + 1], tree[x + 2 * (m - lx + 1)]);
    }
    void push(int x, int lx, int m, int rx) {
        if (lx == rx) {
            tree[x].lazy = 0;
            return;
        }
        tree[x + 1].lazy += tree[x].lazy;
        tree[x + 2 * (m - lx + 1)].lazy += tree[x].lazy;
        tree[x + 1].mn -= tree[x].lazy;
        tree[x + 2 * (m - lx + 1)].mn -= tree[x].lazy;
        tree[x].lazy = 0;
    }
    int get(int x, int lx, int rx, int l, int r) {
        if (l > r) return INT_MAX;
        int m = (lx + rx) >> 1;
        push(x, lx, m, rx);
        if (l == lx && r == rx) return tree[x].mn;
        int s1 = get(x + 1, lx, m, l, min(m, r));
        int s2 = get(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r);
        return min(s1, s2);
    }
};
int n;
void print(Segtree &seg) {
    for (int i = 0; i < n; ++i) {
        cout << seg.get(0, 0, n - 1, i, i) << ' ';
    }
    cout << endl;
}
vector<int> inds;
Segtree seg;
bool check(int mxop) {
    // cout << "mxop: " << mxop << endl;
    int cnt = 0;
    seg.init(inds);
    int could = 0;
    for (int i : inds) {
        int bi = seg.get(0, 0, n - 1, i, i);
        if (bi >= mxop) {
            continue;
        }
        int delta = mxop - bi;
        // cout << "mxop: " << mxop << endl;
        // cout << "i:" << i << endl;
        // cout << "b[i]: " << seg.get(0, 0, n - 1, i, i) << endl;
        // cout << "delta: " << delta << endl;
        int mn = min(seg.get(0, 0, n - 1, 0, i - 1), seg.get(0, 0, n - 1, i + 1, n - 1));
        // cout << "mn: " << mn << endl;
        int to_remove = min({a[i],
                             delta,
                             mn});
        // cout << "to_remove: " << to_remove << endl;
        if (to_remove < delta) {
            return false;
        }
        could += to_remove - delta;
        seg.add(0, 0, n - 1, 0, i - 1, delta);
        seg.add(0, 0, n - 1, i + 1, n - 1, delta);
        mxop -= delta;
    }
    // cout << "RESULT MAXOP: " << mxop << endl;
    return true;
}

void solve() {
    cin >> n;
    a.resize(n);
    b.resize(n);
    int s = 0;
    int s2 = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        s2 += a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        s += b[i];
    }
    s = min(s, s2);
    inds.resize(n);
    iota(inds.begin(), inds.end(), 0);
    sort(inds.begin(), inds.end(), [](int i, int j) {
        return b[i] < b[j];
    });
    int l = 0, r = s + 1;
    while (r - l > 1) {
        int m = (l + r) >> 1;
        if (check(m)) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << l << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}