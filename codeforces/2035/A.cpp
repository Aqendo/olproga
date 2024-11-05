#include "bits/stdc++.h"
#define int int64_t
using namespace std;

void solve() {
    int n, m, r, c;
    cin >> n >> m >> r >> c;
    cout << (m - c) + (m - 1) * (n - r) + (n - r) * m << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) solve();
}
