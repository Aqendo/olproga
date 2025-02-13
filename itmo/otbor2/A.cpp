#include <bits/stdc++.h>
using namespace std;
#define int int64_t
int n, m, q, R, C, x, y, c, opp;
vector<vector<bool>> can_be_reached;
string col;
void solve() {
    cin >> n >> m >> q;
    R = n + 3, C = m + 3;
    vector<vector<int>> grid(R, vector<int>(C, -1));
    for (int move = 0; move < q; move++) {
        cin >> col >> x >> y;
        c = (col == "red") ? 0 : 1;
        opp = 1 - c;
        grid[x + 1][y + 1] = c;
        can_be_reached.assign(R, vector<bool>(C, false));
        queue<pair<int, int>> queries;
        for (int i = 0; i < R; i++) {
            if (!can_be_reached[i][0] && grid[i][0] != c) {
                can_be_reached[i][0] = true;
                queries.push({i, 0});
            }
            if (!can_be_reached[i][C - 1] && grid[i][C - 1] != c) {
                can_be_reached[i][C - 1] = true;
                queries.push({i, C - 1});
            }
        }
        for (int j = 0; j < C; j++) {
            if (!can_be_reached[0][j] && grid[0][j] != c) {
                can_be_reached[0][j] = true;
                queries.push({0, j});
            }
            if (!can_be_reached[R - 1][j] && grid[R - 1][j] != c) {
                can_be_reached[R - 1][j] = true;
                queries.push({R - 1, j});
            }
        }

        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!queries.empty()) {
            auto cur = queries.front();
            queries.pop();
            int i = cur.first, j = cur.second;
            for (auto &d : dirs) {
                int ni = i + d[0], nj = j + d[1];
                if (ni < 0 || ni >= R || nj < 0 || nj >= C) continue;
                if (!can_be_reached[ni][nj] && grid[ni][nj] != c) {
                    can_be_reached[ni][nj] = true;
                    queries.push({ni, nj});
                }
            }
        }
        int cnt = 0;
        for (int i = 1; i <= n + 1; i++) {
            for (int j = 1; j <= m + 1; j++) {
                if (!can_be_reached[i][j] && grid[i][j] == opp) {
                    grid[i][j] = c;
                    cnt++;
                }
            }
        }
        if (cnt == 0) {
            cout << "none" << "\n";
        } else {
            cout << (opp == 0 ? "red" : "green") << " " << cnt << "\n";
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}
