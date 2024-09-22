#include "bits/stdc++.h"
using namespace std;
#define int long long
#define double long double
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

#ifndef SEREGA
#define printf(...)
#define debug(...)
#endif
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> dp(n, vector<int>(n, -1));
    int direction = 0;
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int i = 0, j = 0;
    for (int _ = 0; _ < n * n; ++_) {
        dp[i][j] = _ + 1;
        auto [xOff, yOff] = directions[direction];
        int newX = i + xOff, newY = j + yOff;
        if (newX >= n || newX < 0 || newY >= n || newY < 0 || dp[newX][newY] != -1) {
            direction = (direction + 1) % 4;
            xOff = directions[direction].first;
            yOff = directions[direction].second;
        }
        i += xOff;
        j += yOff;
    }
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            cout << dp[i][j] << ' ';
        }
        cout << '\n';
    }
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
