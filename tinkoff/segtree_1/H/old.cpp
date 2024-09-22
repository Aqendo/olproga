#include <bits/stdc++.h>
using namespace std;
#define int int64_t
int arithmetic(int a1, int k, int len) {
    return (a1 + a1 + k * (len - 1)) * len >> 1;
}
const int MAXN = 1e5 + 42;
struct Arif {
    int a1 = 0;
    int k = 0;
};
struct {
    vector<int> tree = vector<int>(4 * MAXN);
    vector<Arif> arifs = vector<Arif>(4 * MAXN);
    vector<int> adder = vector<int>(4 * MAXN);
    int combine(int x, int lx, int rx, int s1, int s2) {
        int m = (lx + rx) >> 1;
        int res1 = s1 + (m - lx + 1) * adder[x << 1] + arithmetic(arifs[x << 1].a1, arifs[x << 1].k, m - lx + 1);
        int res2 = s2 + (rx - m) * adder[x << 1 | 1] + arithmetic(arifs[x << 1 | 1].a1, arifs[x << 1 | 1].k, rx - m);
        return res1 + res2;
    }
    void push(int x, int lx, int rx) {
        if (lx == rx) {
            tree[x] += arifs[x].a1 + adder[x];
            arifs[x].a1 = 0;
            arifs[x].k = 0;
            adder[x] = 0;
            return;
        }
        int m = (lx + rx) >> 1;
        adder[x << 1] += adder[x];
        adder[x << 1 | 1] += adder[x];
        adder[x] = 0;
        arifs[x << 1].a1 += arifs[x].a1;
        arifs[x << 1].k += arifs[x].k;
        arifs[x << 1 | 1].a1 += arifs[x].a1 + arifs[x].k * (m + 1 - lx);
        arifs[x << 1 | 1].k += arifs[x].k;
        arifs[x] = {0, 0};
        tree[x] = combine(x, lx, rx, tree[x << 1], tree[x << 1 | 1]);
    }
    int get(int l, int r, int x, int lx, int rx) {
        push(x, lx, rx);
        if (l == lx && rx == r) {
            return tree[x];
        }
        if (lx > r || rx < l) return 0;
        int m = (lx + rx) >> 1;
        int s1 = get(l, min(m, r), x << 1, lx, m);
        int s2 = get(max(l, m + 1), r, x << 1 | 1, m + 1, rx);
        return combine(x, lx, rx, s1, s2);
    }
    void addArifm(int l, int r, int a1, int k, int x, int lx, int rx) {
        push(x, lx, rx);
        if (r < lx || rx < l) return;
        if (l == lx && rx == r) {
            arifs[x].a1 += a1;
            arifs[x].k += k;
            push(x, lx, rx);
            return;
        }
        int m = (lx + rx) >> 1;
        addArifm(l, min(m, r), a1, k, x << 1, lx, m);
        addArifm(max(l, m + 1), r, a1 + k * (m + 1 - min(l, m + 1)), k, x << 1 | 1, m + 1, rx);
        tree[x] = combine(x, lx, rx, tree[x << 1], tree[x << 1 | 1]);
    }
    void add(int l, int r, int toAdd, int x, int lx, int rx) {
        push(x, lx, rx);
        if (r < lx || rx < l) return;
        if (l == lx && rx == r) {
            adder[x] += toAdd;
            push(x, lx, rx);
            return;
        }
        int m = (lx + rx) >> 1;
        add(l, min(m, r), toAdd, x << 1, lx, m);
        add(max(l, m + 1), r, toAdd, x << 1 | 1, m + 1, rx);
        tree[x] = combine(x, lx, rx, tree[x << 1], tree[x << 1 | 1]);
    }
} segtree;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        char move;
        cin >> move;
        if (move == '?') {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            cout << segtree.get(l, r, 1, 0, n - 1) << '\n';
        } else if (move == 'C') {
            int l, r, x;
            cin >> l >> r >> x;
            l--;
            r--;
            segtree.add(l, r, -x, 1, 0, n - 1);
        } else {
            int ind, v;
            cin >> ind >> v;
            ind--;
            int lx = max(int(0), ind - v + 1);
            int rx = min(n - 1, ind + v - 1);
            segtree.addArifm(lx, ind, v - (ind - lx), 1, 1, 0, n - 1);
            segtree.addArifm(ind + 1, rx, v - 1, -1, 1, 0, n - 1);
        }
    }
    return 0;
}
