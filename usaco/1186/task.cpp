#include <bits/stdc++.h>
using namespace std;
#define int int64_t

int n, q;

const int N = 2e5 + 78;

const char DEACTIVATE = 'D', ADD_EDGE = 'A', REMOVE_EDGE = 'R';

struct Move {
    char move;
    int x, y;
};

Move moves[N];

int indexStart[N], timerEdge = 0;
pair<int, int> edges[N];

struct Dsu {
    vector<int> sizes, parent;
    void init(int n) {
        sizes.assign(n + 1, 1);
        parent.assign(n + 1, 0);
        iota(parent.begin(), parent.end(), 0);
    }
    int getp(int x) {
        if (parent[x] == x) return x;
        return getp(parent[x]);
    }
};
Dsu dsu;
struct {
    vector<vector<pair<int, int>>> tree;
    void init(int n_) {
        tree.assign(2 * n_ - 1, {});
    }
    void add(int x, int lx, int rx, int l, int r, const pair<int, int> &edge) {
        if (l > r) return;
        if (l == lx && r == rx) {
            tree[x].push_back(edge);
            return;
        }
        int m = (lx + rx) >> 1;
        add(x + 1, lx, m, l, min(m, r), edge);
        add(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r, edge);
    }
    void down(int x, int lx, int rx) {
        vector<pair<int, int>> toReverse;
        toReverse.reserve(tree[x].size());
        for (auto [u, v] : tree[x]) {
            u = dsu.getp(u);
            v = dsu.getp(v);
            if (u == v) continue;
            
        }
    }
} seg;

void solve() {
    cin >> n >> q;
    seg.init(q);
    dsu.init(n + 1);
    for (int i = 0; i < q; ++i) {
        char move;
        cin >> move;
        int x, y = 0;
        cin >> x;
        if (move == ADD_EDGE) cin >> y;
        moves[i] = {move, x, y};
        if (move == ADD_EDGE) {
            indexStart[timerEdge] = i;
            edges[timerEdge] = {x, y};
            timerEdge++;
        } else if (move == REMOVE_EDGE) {
            seg.add(0, 0, q - 1, indexStart[x - 1], i, edges[x - 1]);
        }
    }
    seg.down(0, 0, q - 1);
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
