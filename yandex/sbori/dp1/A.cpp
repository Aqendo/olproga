#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int INF = 1e9 + 7;

void solve() {
    int n, x, answer = 0;
    cin >> n >> x;
    vector<int> t(n + 1), r(n + 2, -INF), lastnvp(n + 1), nvp(n + 2, INF);
    r[0] = INF;
    nvp[0] = -INF;
    for (int i = 1; i <= n; ++i) {
        cin >> t[i];
    }
    for (int i = 1; i <= n; ++i) {
        auto it = lower_bound(nvp.begin(), nvp.end(), t[i]);
        *it = t[i];
        lastnvp[i] = it - nvp.begin();
        answer = max(answer, lastnvp[i]);
    }
    for (int i = n; i >= 1; --i) {
        answer = max(answer, lastnvp[i] + (r.rend() - upper_bound(r.rbegin(), r.rend(), t[i] - x) - 1));
        *--upper_bound(r.rbegin(), r.rend(), t[i]) = t[i];
    }
    cout << answer << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    while (t--) solve();
}