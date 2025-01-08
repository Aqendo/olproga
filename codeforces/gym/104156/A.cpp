#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n, p;
    cin >> n >> p;
    vector<array<int, 3>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
    }
    int l = 0, r = 1e12 + 1;
    auto f = [&a, n](int m) {
        int s = 0;
        for (int i = 0; i < n; ++i) {
            if (m <= a[i][0]) {
                s += a[i][1] * m;
            } else {
                s += a[i][1] * a[i][0] + a[i][2] * (m - a[i][0]);
            }
        }
        return s;
    };
    while (r - l > 1) {
        int m = (l + r) >> 1;
        if (f(m) < p) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << r << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}