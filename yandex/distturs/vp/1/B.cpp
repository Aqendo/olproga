#include <bits/stdc++.h>
using namespace std;
#define int int64_t

int f(int x, int y) {
    return x + 2 * x * y + y;
}

void solve() {
    int k;
    cin >> k;
    // vector<int> xs;
    // for (int i = 1; i * i <= k; ++i) {
    //     if (k % i == 0) {
    //         xs.push_back(i);
    //     }
    // }
    int mx = LLONG_MIN, mn = LLONG_MAX;
    for (int x = 1; x <= int(sqrt(k)) + 3; ++x) {
        int y = (k - x) / (2 * x + 1);
        if (y > 0 && f(x, y) == k) {
            mx = max(mx, y * x);
            mn = min(mn, y * x);
        }
    }
    if (mn == LLONG_MAX) {
        cout << -1 << '\n';
        return;
    }
    cout << mn << ' ' << mx << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}
