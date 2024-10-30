#include "bits/stdc++.h"
using namespace std;

vector<vector<int>> g;

void solve() {
    int n, m;
    cin >> n >> m;
    g.assign(n * m, {});
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i + 1 < n) {
                g[(i + 1) * m + j].push_back(i * m + j);
                g[i * m + j].push_back((i + 1) * m + j);
            }
            if (j + 1 < m) {
                g[i * m + j].push_back(i * m + j + 1);
                g[i * m + j + 1].push_back(i * m + j);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        g[i * m].push_back((i + 1) * m - 1);
        g[(i + 1) * m - 1].push_back(i * m);
    }
    for (int j = 0; j < m; ++j) {
        g[j].push_back((n - 1) * m + j);
        g[(n - 1) * m + j].push_back(j);
    }
    vector<int> verticies(n * m);
    iota(verticies.begin(), verticies.end(), 0);
    sort(verticies.begin(), verticies.end(), [](int x, int y) { return g[x].size() > g[y].size(); });
    vector<int> color(n * m);
    for (int col = 1; col <= n * m; ++col) {
        for (int i = 0; i < n * m; ++i) {
            if (color[verticies[i]]) continue;
            bool good = true;
            for (int u : g[verticies[i]]) {
                if (color[u] == col) {
                    good = false;
                    break;
                }
            }
            if (good) {
                color[verticies[i]] = col;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << color[i * m + j] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
