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
vector<int> depths;
pair<vector<int>, int> get_longest_bfs(int x) {
    queue<pair<int, int>> q;
    // path, vertex
    q.push({1, x});
    used[x] = true;
    vector<int> last = {x};
    int max_depth = 0;
    while (!q.empty()) {
        auto [depth, vertex] = q.front();
        q.pop();
        depths[vertex] = depth;
        if (max_depth == depth) {
            last.push_back(vertex);
        } else if (max_depth < depth) {
            max_depth = depth;
            last = {vertex};
        }
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
    depths.assign(n, {});
    auto [from_what, _] = get_longest_bfs(0);
    depths.assign(n, {});
    used.assign(n, {});
    int res = INT_MIN;
    for (int i : from_what) {
        auto [vert_, res_] = get_longest_bfs(i);
        res = max(res, res_);
    }
    cout << res << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 1) {
                if (abs(depths[i] - depths[j]) != 1) {
                    exit(1);
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (depths[i] == 0) exit(1);
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
