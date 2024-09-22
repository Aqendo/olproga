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

const int MAXN = 100000;

struct Node {
    int amountRight;
    int amountLeft;
    int maxAmount;
    int len;
    bool operator==(const Node& lhs) const {
        return amountRight == lhs.amountRight && amountLeft == lhs.amountLeft && maxAmount == lhs.maxAmount && len == lhs.len;
    }
};

const Node null = {0, 0, 0, 0};
Node oneElement(int val) {
    return {val == 1, val == 1, val == 1, 1};
}
struct {
    vector<Node> tree = vector<Node>(MAXN * 4, null);
    Node combine(Node& n1, Node& n2) {
        if (n1 == null) return n2;
        if (n2 == null) return n1;
        return {(n2.amountRight == n2.len ? n1.amountRight + n2.amountRight : n2.amountRight),
                (n1.amountLeft == n1.len ? n1.amountLeft + n2.amountLeft : n1.amountLeft), max({n1.maxAmount, n2.maxAmount, n1.amountRight + n2.amountLeft}),
                n1.len + n2.len};
    }
    void build(vector<int>& arr, int x, int lx, int rx) {
        if (lx == rx) {
            if (lx < arr.size()) {
                tree[x] = oneElement(arr[lx]);
            }
            return;
        }
        int m = (lx + rx) >> 1;
        build(arr, x << 1, lx, m);
        build(arr, x << 1 | 1, m + 1, rx);
        tree[x] = combine(tree[x << 1], tree[x << 1 | 1]);
    }
    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx) {
            tree[x] = oneElement(v);
            return;
        }
        int m = (lx + rx) >> 1;
        if (i <= m) {
            set(i, v, x << 1, lx, m);
        } else {
            set(i, v, x << 1 | 1, m + 1, rx);
        }
        tree[x] = combine(tree[x << 1], tree[x << 1 | 1]);
    }

    Node get(int l, int r, int x, int lx, int rx) {
        if (lx == l && rx == r) {
            return tree[x];
        }
        if (lx > r || rx < l) {
            return null;
        }
        int m = (lx + rx) >> 1;
        Node s1 = get(l, min(m, r), x << 1, lx, m);
        Node s2 = get(max(l, m + 1), r, x << 1 | 1, m + 1, rx);
        return combine(s1, s2);
    }
} segtree;

int n;
void print() {
    for (int i = 0; i < n; ++i) {
        cout << segtree.get(i, i, 1, 0, n - 1).maxAmount << ' ';
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<int> razn(n + 1);
    cin >> razn[0];
    int t = razn[0];
    for (int i = 1; i < n; ++i) {
        int now;
        cin >> now;
        razn[i] = now - t;
        t = now;
    }
    segtree.build(razn, 1, 0, n);
    int q;
    cin >> q;
    debug(razn);
    for (int i = 0; i < q; ++i) {
        char move;
        cin >> move;
        if (move == '?') {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            int ans = segtree.get(l + 1, r, 1, 0, n).maxAmount;
            ans++;
            cout << ans << '\n';
        } else {
            int l, r, d;
            cin >> l >> r >> d;
            l--;
            r--;
            razn[l] += d;
            if (r + 1 < n) {
                razn[r + 1] -= d;
            }
            segtree.set(l, razn[l], 1, 0, n);
            if (r + 1 < n) {
                segtree.set(r + 1, razn[r + 1], 1, 0, n);
            }
            debug(razn);
        }
    }
    return 0;
}