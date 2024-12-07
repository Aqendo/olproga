#include <bits/stdc++.h>
#define int int64_t
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    if (k <= n / k) {
        cout << 0 << '\n';
        return;
    }
    int cnt_full = (k) / (n / k);
    // cout << cnt_full << endl;
    int pairs = (cnt_full * (cnt_full - 1) / 2) * (n / k);
    int remain = (k) % (n / k);
    if (cnt_full > 0) {
        pairs += remain * cnt_full;
    }
    cout << pairs * (n / k) << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
