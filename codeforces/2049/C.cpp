#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    if (x > y) swap(x, y);
    if (n % 2 == 0) {
        if (x == y - 1 || (x == 1 && y == n)) {
            for (int i = 0; i < n; ++i) {
                cout << "01"[i % 2] << ' ';
            }
            cout << '\n';
            return;
        }
        if ((y - x) & 1) {
            for (int i = 1; i <= n; ++i) {
                cout << "10"[i % 2] << ' ';
            }
        } else {
            for (int i = 1; i <= n; ++i) {
                if (i == y) {
                    cout << 2 << ' ';
                } else {
                    cout << "10"[i % 2] << ' ';
                }
            }
        }
        cout << '\n';
        return;
    }
    vector<int> a(n);
    y--;
    for (int i = 1; i < n; ++i) {
        a[(i + y) % n] = i & 1;
    }
    a[y] = 2;
    for (int i : a) cout << i << ' ';
    cout << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}