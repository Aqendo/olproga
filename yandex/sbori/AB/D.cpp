#include <bits/stdc++.h>
using namespace std;
#define int int64_t


void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n + 1), pref(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pref[i] = pref[i - 1] + (a[i] >= x);
    }
    int l = 1, r = n;
    int m;
    cin >> m;
    vector<pair<int, int>> queries(m);
    for (int i = 0; i < m; ++i) {
        int move, xx = 0;
        cin >> move;
        if (move != 2) cin >> xx;
        queries[i] = {move, xx};
        if (move == 1) {
            a.push_back(xx);
            pref.push_back(pref.back() + (xx >= x));
        }
    }
    for (int i = 0; i < m; ++i) {
        auto [move, xx] = queries[i];
        if (move == 1) {
            r++;
            continue;
        } else if (move == 2) {
            l++;
            continue;
        }
        cout << pref[l - 1 + xx] - pref[l - 1] << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}