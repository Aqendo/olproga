#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<vector<int>> grid;
vector<vector<int>> pref;

/*
    t
 ________
 |
 |
s|
 |
 |
*/

// Standard prefix-sum query: returns the sum of the submatrix with top-left (lefti, leftj)
// and dimensions s x t.
int get(int lefti, int leftj, int s, int t) {
    return pref[lefti + s - 1][leftj + t - 1] - pref[lefti - 1][leftj + t - 1] - pref[lefti + s - 1][leftj - 1] + pref[lefti - 1][leftj - 1];
}

int s, t;  // dimensions (or one orientation) for the third rectangle.
int n, m;
int mx = 0;

// New conflict function: returns true if the two rectangles either overlap (share any cell)
// or “touch” along a full edge. (They may still be allowed if they merely meet at a corner.)
bool conflict(int i1, int j1, int h1, int w1,
              int i2, int j2, int h2, int w2) {
    // Check for overlapping cells.
    if (i1 <= i2 + h2 - 1 && i2 <= i1 + h1 - 1 &&
        j1 <= j2 + w2 - 1 && j2 <= j1 + w1 - 1) {
        return true;
    }
    // Check horizontal edge-touch.
    if ((j1 + w1 == j2 || j2 + w2 == j1) &&
        (i1 <= i2 + h2 - 1 && i2 <= i1 + h1 - 1)) {
        return true;
    }
    // Check vertical edge-touch.
    if ((i1 + h1 == i2 || i2 + h2 == i1) &&
        (j1 <= j2 + w2 - 1 && j2 <= j1 + w1 - 1)) {
        return true;
    }
    return false;
}

void find3(int first, int second, int down, int right,
           int first1, int second1, int down1, int right1) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            // Consider the third rectangle in one orientation.
            if (i + s - 1 <= n && j + t - 1 <= m) {
                if (!conflict(first, second, down, right, i, j, s, t) &&
                    !conflict(first1, second1, down1, right1, i, j, s, t)) {
                    mx = max(mx, get(first, second, down, right) +
                                     get(first1, second1, down1, right1) +
                                     get(i, j, s, t));
                }
            }
            // Also try the rotated orientation.
            if (i + t - 1 <= n && j + s - 1 <= m) {
                if (!conflict(first, second, down, right, i, j, t, s) &&
                    !conflict(first1, second1, down1, right1, i, j, t, s)) {
                    mx = max(mx, get(first, second, down, right) +
                                     get(first1, second1, down1, right1) +
                                     get(i, j, t, s));
                }
            }
        }
    }
}

void find(int first, int second, int down, int right) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            // Second rectangle in one orientation.
            if (i + s - 1 <= n && j + t - 1 <= m) {
                if (!conflict(first, second, down, right, i, j, s, t)) {
                    find3(first, second, down, right, i, j, s, t);
                }
            }
            // Second rectangle rotated.
            if (i + t - 1 <= n && j + s - 1 <= m) {
                if (!conflict(first, second, down, right, i, j, t, s)) {
                    find3(first, second, down, right, i, j, t, s);
                }
            }
        }
    }
}

void solve() {
    cin >> n >> m;
    grid.assign(n + 1, vector<int>(m + 1));
    pref.assign(n + 1, vector<int>(m + 1));
    // Read grid and build prefix sums.
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> grid[i][j];
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + grid[i][j];
        }
    }
    cin >> s >> t;
    // Try every possible placement and orientation for the first rectangle.
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i + s - 1 <= n && j + t - 1 <= m) {
                find(i, j, s, t);
            }
            if (i + t - 1 <= n && j + s - 1 <= m) {
                find(i, j, t, s);
            }
        }
    }
    cout << mx << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
