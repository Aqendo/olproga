#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n - (k - 1); ++i) {
        if (a[i] != 1) {
            cout << 1 << '\n';
            return;
        }
    }
    if (k != n) {
        cout << 2 << '\n';
        return;
    }
    int timer = 1;
    a.push_back(0);
    a.push_back(0);
    for (int i = 1; i < n + 2; i += 2) {
        if (timer != a[i]) {
            cout << timer << '\n';
            return;
        }
        timer++;
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}
