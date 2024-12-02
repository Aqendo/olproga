#include "bits/stdc++.h"
using namespace std;
#define int int64_t

void solve() {
    int n, m;
    cin >> n >> m;
    if (m < n) {
        cout << -1 << endl;
        return;
    }
    for (int i = 0; i < n - 1; ++i) {
        cout << 1 << ' ';
        m--;
    }
    cout << m << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) solve();
}
