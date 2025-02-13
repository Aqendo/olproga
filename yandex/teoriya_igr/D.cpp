#include <bits/stdc++.h>
using namespace std;
%:define int int64_t

int get(int n) {
    int vals[] = {n, 1, n + 1, 0};
    return vals[n % 4];
}

void solve() {
    int n;
    cin >> n;
    vector<int[2]> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i][0] >> a[i][1];
    }
    int xord = 0;
    for (int i = 0; i < n; ++i) {
        xord ^= get(a[i][1]) ^ get(a[i][0] - 1);
    }
    cout << (xord ? "Win" : "Lose") << '\n';
    if (xord) {
        for (int i = 0; i < n; ++i) {
            for (int old = a[i][1]; old >= max(a[i][1] - 100, a[i][0]); --old) {
                if ((xord ^ old) < old) {
                    cout << old << ' ' << (xord ^ old) << '\n';
                    return;
                }
            }
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
