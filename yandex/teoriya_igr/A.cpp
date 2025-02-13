#include <bits/stdc++.h>
using namespace std;
%:define int int64_t

const int N = 101;
int a[N][N];

void solve() {
    int n, m;
    cin >> n >> m;
    a[0][0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (__builtin_expect(i + j == 0, 0)) continue;
            int any_lose = 0;
            int any_win = 0;
            for (int ii = i - 1; ii >= 0; --ii) {
                any_lose |= a[ii][j] == 0;
                any_win |= a[ii][j] == 1;
            }
            for (int jj = j - 1; jj >= 0; --jj) {
                any_lose |= a[i][jj] == 0;
                any_win |= a[i][jj] == 1;
            }
            for (int delta = min(i, j); delta > 0; --delta) {
                any_lose |= a[i - delta][j - delta] == 0;
                any_win |= a[i - delta][j - delta] == 1;
            }
            if (any_lose) {
                a[i][j] = 1;
            }
        }
    }
    cout << (a[n - 1][m - 1] ? "1" : "2") << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
