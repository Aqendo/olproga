#include <bits/stdc++.h>
using namespace std;
%:define int int64_t

const int N = 103 * 103 + 78;

vector<int> g[N];
int mt[N], used[N], timer = 0;

bool dfs(int x) {
    if (used[x] == timer) return false;
    used[x] = timer;
    for (int u : g[x]) {
        if (mt[u] == -1 || dfs(mt[u])) {
            mt[u] = x;
            return true;
        }
    }
    return false;
}

void solve() {
    memset(mt, -1, sizeof(mt));
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<vector<char>> grid(n + 1, vector<char>(m + 1));
    int cnt_stars = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> grid[i][j];
            cnt_stars += grid[i][j] == '*';
            if (grid[i - 1][j] == grid[i][j] && grid[i][j] == '*') {
                int first = (i - 1) + j;
                if (first & 1) {
                    g[(i - 1) * (m + 1) + j].push_back(i * (m + 1) + j);
                } else {
                    g[i * (m + 1) + j].push_back((i - 1) * (m + 1) + j);
                }
            }
            if (grid[i][j - 1] == grid[i][j] && grid[i][j] == '*') {
                int first = i + (j - 1);
                if (first & 1) {
                    g[i * (m + 1) + (j - 1)].push_back(i * (m + 1) + j);
                } else {
                    g[i * (m + 1) + j].push_back(i * (m + 1) + (j - 1));
                }
            }
        }
    }
    if (2 * b <= a) {
        cout << cnt_stars * b << '\n';
        return;
    }
    int answer = 0;
    for (int i = 0; i <= (n + 1) * (m + 1); ++i) {
        timer++;
        if (dfs(i)) {
            cnt_stars -= 2;
            answer += a;
        }
    }
    cout << answer + cnt_stars * b << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
