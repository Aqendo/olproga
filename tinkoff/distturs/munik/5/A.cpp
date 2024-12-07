#include <bits/stdc++.h>
#define int int64_t
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    cout << n / k + (n % k != 0) << ' ' << max<int>(1, n - k + 1) << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
