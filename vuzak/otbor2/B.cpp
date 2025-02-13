#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n, m, t;
    cin >> n >> m >> t;
    int answer = 0;
    for (int y = 1; y <= n; ++y) {
        int xmeq = max<int>(1, (t - y + 2 * y) / (2 * y + 1));
        answer += max<int>(0, m - xmeq + 1);
    }
    cout << answer << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
