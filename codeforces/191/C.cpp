#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<vector<int>> g;
vector<int> s, p;
vector<int> eulers, tin, tout, head, used;
int timer = 0;

void sizes(int x) {
    s[x] = 1;
    for (int& u : g[x]) {
        if (s[u]) continue;
        p[u] = x;
        sizes(u);
        s[x] += s[u];
        if (s[u] > s[g[x][0]]) {
            swap(u, g[x][0]);
        }
    }
}

void heads(int x) {
    tin[x] = timer++;
    used[x] = true;
    for (int u : g[x]) {
        if (used[u]) continue;
        if (u == g[x][0]) {
            head[u] = head[x];
        } else {
            head[u] = u;
        }
        heads(u);
    }
    tout[x] = timer;
}

bool is_ancestor(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

struct Node {
    int v;
    int lazy;
    void combine(const Node& l, const Node& r) { v = l.v + r.v; }
};
struct Segtree {
    vector<Node> tree;
    Segtree(int n) : tree(2 * (n + 1) - 1) {}
    void add(int x, int lx, int rx, int l, int r, int toadd) {
        if (l > r) return;
        if (l == lx && r == rx) {
            tree[x].lazy += toadd;
            tree[x].v += toadd * (rx - lx + 1);
            return;
        }
        int m = (lx + rx) >> 1;
        push(x, lx, m, rx);
        add(x + 1, lx, m, l, min(m, r), toadd);
        add(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r, toadd);
        tree[x].combine(tree[x + 1], tree[x + 2 * (m - lx + 1)]);
    }
    int get(int x, int lx, int rx, int i) {
        int m = (lx + rx) >> 1;
        push(x, lx, m, rx);
        if (lx == rx) return tree[x].v;
        if (i <= m) {
            return get(x + 1, lx, m, i);
        } else {
            return get(x + 2 * (m - lx + 1), m + 1, rx, i);
        }
    }
    void push(int x, int lx, int m, int rx) {
        if (lx == rx) {
            tree[x].lazy = 0;
            return;
        }
        tree[x + 1].v += tree[x].lazy * (m - lx + 1);
        tree[x + 2 * (m - lx + 1)].v += tree[x].lazy * (rx - m);
        tree[x + 1].lazy += tree[x].lazy;
        tree[x + 2 * (m - lx + 1)].lazy += tree[x].lazy;
        tree[x].lazy = 0;
    }
};
int n;
void up(Segtree& seg, int& a, int& b) {
    while (!is_ancestor(head[a], b)) {
        seg.add(0, 0, n, tin[head[a]], tin[a], 1);
        a = p[head[a]];
    }
}

void solve() {
    cin >> n;
    g.assign(n + 1, {});
    s.assign(n + 1, {});
    tin.assign(n + 1, {});
    tout.assign(n + 1, {});
    head.assign(n + 1, {});
    used.assign(n + 1, {});
    eulers.assign(n + 1, {});
    Segtree seg(n + 1);
    p.assign(n + 1, {});
    vector<pair<int, int>> edges(n - 1);
    for (int i = 1; i <= n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        edges[i - 1] = {a, b};
        g[a].push_back(b);
        g[b].push_back(a);
    }
    head[1] = 1;
    p[1] = 1;
    sizes(1);
    heads(1);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        int old_a = a, old_b = b;
        int answer = 0;
        up(seg, a, b);
        up(seg, b, a);
        if (tin[a] > tin[b]) {
            swap(a, b);
        }
        seg.add(0, 0, n, tin[a], tin[b], 1);
        while (!is_ancestor(a, b)) {
            a = p[a];
        }
        seg.add(0, 0, n, tin[a], tin[a], -1);
    }
    map<pair<int, int>, int> answer_for_edge;
    for (int i = 2; i <= n; ++i) {
        if (i != p[i]) {
            answer_for_edge[{p[i], i}] = answer_for_edge[{i, p[i]}] = seg.get(0, 0, n, tin[i]);
        }
    }
    for (auto& [u, w] : edges) {
        cout << answer_for_edge[{u, w}] << ' ';
    }
    cout << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}