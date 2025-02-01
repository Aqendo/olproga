#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, int> cnt;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        int c = 1ll << __builtin_ctzll(a[i]);
        cnt[a[i] / c] += c;
    }
    int mx = 0;
    for (auto [u, w] : cnt) {
        mx = max<int>(mx, u * (1ll << (63 - __builtin_clzll(w))));
    }
    cout << mx << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    while (t--) solve();
}