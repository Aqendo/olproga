#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n, x;
    cin >> n >> x;
    int num = 1;
    for (int i = 0; i < n; ++i) {
        num *= 10;
    }
    num--;
    if ((1ll << x) > num) {
        cout << 0 << endl;
        return;
    }
    int full = (num >> x);
    num = 1;
    for (int i = 0; i < n - 1; ++i) {
        num *= 10;
    }
    num--;
    int from = (num >> x);
    cout << full << ' ' << from << endl;
    cout << full - from << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}