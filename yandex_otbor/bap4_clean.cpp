#include "bits/stdc++.h"

using namespace std;
#define int long long
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

vector<int> used;
vector<char> color;
vector<vector<int>> g;
bool good = true;
void dfs(int x) {
    if (!good) return;
    used[x] = true;
    int color_neighbors = -1;
    for (int u : g[x]) {
        if (color[u] != -1) {
            if (color_neighbors != -1) {
                if (color[u] != color_neighbors) {
                    good = false;
                    return;
                }
            } else {
                color_neighbors = color[u];
            }
        }
    }
    if (color_neighbors == -1) color_neighbors = 3;
    color[x] = color_neighbors ^ 1;
    for (int u : g[x]) {
        if (!used[u]) {
            dfs(u);
        }
    }
}
const int INF = 1e9;
pair<int, int> get_longest_bfs(int x) {
    queue<pair<int, int>> q;
    // path, vertex
    q.push({0, x});
    used[x] = true;
    int last = x;
    int max_depth = 0;
    while (!q.empty()) {
        auto [depth, vertex] = q.front();
        q.pop();
        last = vertex;
        max_depth = depth;
        for (int u : g[vertex]) {
            if (!used[u]) {
                q.push({depth + 1, u});
                used[u] = true;
            }
        }
    }
    return {last, max_depth};
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    used.assign(n, {});
    color.assign(n, -1);
    g.assign(n, {});
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c;
            cin >> c;
            grid[i][j] = c - '0';
            if (grid[i][j]) {
                g[i].push_back(j);
            } else {
                grid[i][j] = INF;
            }
        }
    }
    dfs(0);
    if (!good) {
        cout << "-1\n";
        return;
    }
    used.assign(n, {});
    auto [from_what, _] = get_longest_bfs(0);
    used.assign(n, {});
    auto [vert_, res] = get_longest_bfs(from_what);
    cout << res + 1 << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
