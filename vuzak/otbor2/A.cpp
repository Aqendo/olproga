#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n, m;
    cin >> n >> m;
    int answer = 0;
    int now = 0;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        now += t;
        if (now >= m) {
            now %= m;
            answer += now == 0;
        }
    }
    cout << answer << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
