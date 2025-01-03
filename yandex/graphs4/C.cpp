#include <bits/stdc++.h>
using namespace std;

const int LOG_MAX = 19;
vector<vector<pair<int, int>>> g;
vector<vector<int>> binup;
vector<vector<int>> binup_minedge;
vector<int> h;
vector<int> tin, tout;
int timer = 0;
void dfs(int x, int last_weight = INT_MAX, int parent = -1, int height = 0) {
    tin[x] = timer++;
    h[x] = height;
    if (parent == -1) {
        parent = x;
    }
    binup[x][0] = parent;
    binup_minedge[x][0] = last_weight;
    for (int lg_ = 1; lg_ <= LOG_MAX; ++lg_) {
        binup[x][lg_] = binup[binup[x][lg_ - 1]][lg_ - 1];
        binup_minedge[x][lg_] = min(binup_minedge[x][lg_ - 1], binup_minedge[binup[x][lg_ - 1]][lg_ - 1]);
    }
    for (auto [u, w] : g[x]) {
        if (u == parent) continue;
        dfs(u, w, x, height + 1);
    }
    tout[x] = timer++;
}

bool is_ancestor(int x, int y) {
    return tin[x] <= tin[y] && tout[y] <= tout[x];
}

int lca(int x, int y) {
    if (h[x] < h[y]) {
        swap(x, y);
    }
    int diff = h[x] - h[y];
    int answer = INT_MAX;
    for (int bit = 19; bit >= 0; --bit) {
        if (diff >> bit & 1) {
            answer = min(answer, binup_minedge[x][bit]);
            x = binup[x][bit];
        }
    }
    assert(h[x] == h[y]);
    for (int bit = 19; bit >= 0; --bit) {
        if (x == y) break;
        if (binup[x][bit] != binup[y][bit]) {
            answer = min({answer, binup_minedge[x][bit], binup_minedge[y][bit]});
            x = binup[x][bit];
            y = binup[y][bit];
        }
    }
    if (x != y) {
        answer = min({answer, binup_minedge[x][0], binup_minedge[y][0]});
    }
    return answer;
}

void solve() {
    int n;
    cin >> n;
    g.assign(n + 1, {});
    h.assign(n + 1, {});
    tin.assign(n + 1, {});
    tout.assign(n + 1, {});
    binup.assign(n + 1, vector<int>(LOG_MAX + 1));
    binup_minedge.assign(n + 1, vector<int>(LOG_MAX + 1, INT_MAX));
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back({i + 2, y});
    }
    // for (int i = 1; i <= n; ++i) {
    //     for (auto [u, w] : g[i]) {
    //         cout << i << ' ' << u << ' ' << w << '\n';
    //     }
    // }
    dfs(1);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        cout << lca(x, y) << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
