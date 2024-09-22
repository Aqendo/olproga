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

const int MAXN = 500000;

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
    return {val == 0, val == 0, val == 0, 1};
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
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int& i : arr) cin >> i;
    segtree.build(arr, 1, 0, n - 1);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        string move;
        cin >> move;
        if (move == "QUERY") {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            cout << segtree.get(l, r, 1, 0, n - 1).maxAmount << '\n';
        } else {
            int ind, val;
            cin >> ind >> val;
            ind--;
            segtree.set(ind, val, 1, 0, n - 1);
        }
    }
    return 0;
}