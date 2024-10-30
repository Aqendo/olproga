#include <bits/stdc++.h>
#define int int64_t
using namespace std;

/*
1 - 90 по часовой
2 - 90 против часовой
3 - 45 по часовой
4 - 45 против часов
*/

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
        }
    }
    int degree = 0;
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            degree += 90;
        } else if (t == 2) {
            degree -= 90;
        } else if (t == 3) {
            degree += 45;
        } else {
            degree -= 45;
        }
    }
    degree = ((degree % 360) + 360) % 360;
    int left = 0, right = 0;
    if (degree == 0) {
        for (int i = 0; i < n; ++i) {
            left += g[i][0];
            right += g[i][n - 1];
        }
    } else if (degree == 45) {
        left = g[n - 1][0];
        right = g[0][n - 1];
    } else if (degree == 90) {
        for (int i = 0; i < n; ++i) {
            right += g[0][i];
        }
        for (int i = 0; i < n; ++i) {
            left += g[n - 1][i];
        }
    } else if (degree == 90 + 45) {
        left = g[n - 1][n - 1];
        right = g[0][0];
    } else if (degree == 180) {
        for (int i = 0; i < n; ++i) {
            right += g[i][0];
            left += g[i][n - 1];
        }
    } else if (degree == 180 + 45) {
        left = g[0][n - 1];
        right = g[n - 1][0];
    } else if (degree == 180 + 90) {
        for (int i = 0; i < n; ++i) {
            left += g[0][i];
        }
        for (int i = 0; i < n; ++i) {
            right += g[n - 1][i];
        }
    } else {
        left = g[0][0];
        right = g[n - 1][n - 1];
    }
    cout << left << " " << right << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}