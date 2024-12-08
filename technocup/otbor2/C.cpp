#include <bits/stdc++.h>
#define int int64_t
using namespace std;

void solve() {
    int n, m, b;
    cin >> n >> m >> b;
    swap(n, m);
    vector<vector<array<int, 27>>> power(n, vector<array<int, 27>>(m));
    for (int al = 0; al < b; ++al) {
        int x, y, i;
        cin >> x >> y >> i;
        for (int ii = -n - 3; ii < 2 * n + 2; ++ii) {
            for (int jj = -m - 3; jj < 2 * m + 2; ++jj) {
                power[(ii + 3 * n) % n][(jj + 3 * m) % m][al] = max<int>(power[(ii + 3 * n) % n][(jj + 3 * m) % m][al], i - (abs(ii - y) + abs(jj - x)));
            }
        }
    }
    vector<vector<int>> result(n, vector<int>(m, 0));
    vector<vector<char>> grid(n, vector<char>(m, '#'));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int cnt = 1e9, mx = -1e9, el = -1e9;
            for (int al = 0; al < b; ++al) {
                if (power[i][j][al] > mx) {
                    cnt = 1, mx = power[i][j][al];
                    el = al;
                } else if (power[i][j][al] == mx) {
                    cnt++;
                }
            }
            if (cnt == 1) {
                result[i][j] = power[i][j][el];
                if (power[i][j][el] != 0)
                    grid[i][j] = el + 'a';
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << grid[i][j];
        }
        cout << endl;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << result[i][j];
            if (j != m - 1)
                cout << ' ';
        }
        if (i != n - 1)
            cout << endl;
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
