#include <bits/stdc++.h>

using namespace std;

int64_t MOD;
const int64_t p = 27;
int64_t pp[100002];
struct Node {
    int64_t hash;
    int64_t len;
};
struct Segtree {
    vector<Node> tree;
    Segtree(int64_t n) : tree(4 * n) {}
    Node combine(Node l, Node r) { return {(l.hash * pp[r.len] + r.hash) % MOD, l.len + r.len}; }
    void build(string& s, int64_t x, int64_t lx, int64_t rx) {
        if (lx == rx) {
            if (lx < s.size()) {
                tree[x] = {s[lx], 1};
            }
            return;
        }
        int64_t m = (lx + rx) >> 1;
        build(s, x << 1, lx, m);
        build(s, x << 1 | 1, m + 1, rx);
        tree[x] = combine(tree[x << 1], tree[x << 1 | 1]);
    }
    Node get(int64_t x, int64_t lx, int64_t rx, int64_t l, int64_t r) {
        if (l > r) return {0, 0};
        if (lx == l && rx == r) {
            return tree[x];
        }
        int64_t m = (lx + rx) >> 1;
        Node g1 = get(x << 1, lx, m, l, min(r, m));
        Node g2 = get(x << 1 | 1, m + 1, rx, max(l, m + 1), r);
        return combine(g1, g2);
    }
    void set(int64_t x, int64_t lx, int64_t rx, int64_t i, int64_t v) {
        if (lx == rx) {
            tree[x] = {v, 1};
            return;
        }
        int64_t m = (lx + rx) >> 1;
        if (i <= m) {
            set(x << 1, lx, m, i, v);
        } else {
            set(x << 1 | 1, m + 1, rx, i, v);
        }
        tree[x] = combine(tree[x << 1], tree[x << 1 | 1]);
    }
};
void solve() {
    string s, reversed;
    cin >> s;
    reversed = s;
    reverse(reversed.begin(), reversed.end());
    int64_t m;
    cin >> m;
    int64_t n = s.size();
    Segtree norm(n);
    norm.build(s, 1, 0, n - 1);
    Segtree rev(n);
    rev.build(reversed, 1, 0, n - 1);
    for (int64_t i = 0; i < m; ++i) {
        string move;
        cin >> move;
        if (move[0] == 'p') {
            int64_t j, k;
            cin >> j >> k;
            j--;
            k--;
            int64_t len = k - j + 1;
            Node h1 = norm.get(1, 0, n - 1, j, j + len / 2 - 1);
            int64_t coord_next_x = k - len / 2 + 1;
            int64_t coord_next_y = k;
            Node h2 = rev.get(1, 0, n - 1, n - 1 - coord_next_y, n - 1 - coord_next_x);
            if (h1.hash == h2.hash && h1.len == h2.len) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        } else {
            int64_t index;
            char a;
            cin >> index >> a;
            norm.set(1, 0, n - 1, index - 1, (int64_t)a);
            rev.set(1, 0, n - 1, n - index, (int64_t)a);
        }
    }
}
bool is_prime(int64_t n) {
    if (n <= 2) return true;  // ну и что что 1 не простое число :)
    for (int64_t i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

void gen_mod() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    MOD = uniform_int_distribution<int64_t>(1000000000, 2000000000)(rng);
    while (!is_prime(MOD)) {
        MOD = uniform_int_distribution<int64_t>(1000000000, 2000000000)(rng);
    }
}
void precalc_p() {
    pp[0] = 1;
    for (int64_t i = 1; i <= 100001; ++i) {
        pp[i] = (pp[i - 1] * p) % MOD;
    }
}
signed main() {
    gen_mod();
    precalc_p();
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}