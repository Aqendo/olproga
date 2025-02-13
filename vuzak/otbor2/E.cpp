#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 2e5 + 78;

int n, s, t, q, timer = 0;

int tin[N], tout[N], cost[N], binup[21][N];
vector<pair<int, int>> g[N];

void dfs(int x, int par = -1, int already = 0) {
    if (par == -1) par = x;
    binup[0][x] = par;
    for (int log_ = 1; log_ < 21; ++log_) {
        binup[log_][x] = binup[log_ - 1][binup[log_ - 1][x]];
    }
    tin[x] = timer++;
    cost[x] = already;
    for (auto [u, w] : g[x]) {
        if (u != par) {
            dfs(u, x, already + w);
        }
    }
    tout[x] = timer++;
}
bool is_ancestor(int x, int y) {
    return tin[x] < tin[y] && tout[y] < tout[x];
}
bool is_ancestore(int x, int y) {
    return tin[x] <= tin[y] && tout[y] <= tout[x];
}

int getlca(int a, int b) {
    if (is_ancestor(a, b)) {
        return a;
    }
    if (is_ancestor(b, a)) {
        return b;
    }
    for (int up = 20; up >= 0; --up) {
        if (!is_ancestor(binup[up][a], b)) {
            a = binup[up][a];
        }
    }
    return binup[0][a];
}
int get(int a, int b) {
    if (is_ancestore(a, b)) {
        return cost[b] - cost[a];
    }
    if (is_ancestore(b, a)) {
        return cost[a] - cost[b];
    }
    int lca = getlca(a, b);
    return cost[a] + cost[b] - 2 * cost[lca];
}
#define in_subtree(x) is_ancestore(b1, (x))
int getanswer(int a1, int b1, int a2, int b2, int c) {
    if (!is_ancestor(a1, b1)) {
        swap(a1, b1);
    }
    if (is_ancestore(b2, a2)) {
        swap(b2, a2);
    }
    int ans = LLONG_MAX;
    if (in_subtree(s) == in_subtree(t)) {
        ans = min(ans, get(s, t));
    }
    if (in_subtree(s) == in_subtree(a2) && in_subtree(b2) == in_subtree(t)) {
        ans = min(ans, get(s, a2) + c + get(b2, t));
    }
    if (in_subtree(s) == in_subtree(b2) && in_subtree(a2) == in_subtree(t)) {
        ans = min(ans, get(s, b2) + c + get(a2, t));
    }
    if (ans == LLONG_MAX) ans = -1;
    return ans;
}
void solve() {
    cin >> n >> s >> t;
    for (int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }

    dfs(1);

    cin >> q;
    for (int lol = 0; lol < q; ++lol) {
        int a1, b1, a2, b2, c;
        cin >> a1 >> b1 >> a2 >> b2 >> c;

        cout << getanswer(a1, b1, a2, b2, c) << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
