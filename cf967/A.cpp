#include "bits/stdc++.h"
#define int long long

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
#endif

void solve() {
    int n;
    cin >> n;
    map<int, int> cnt;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        cnt[t]++;
    }
    int mx = INT_MIN;
    for (auto [u, v] : cnt) {
        mx = max(mx, v);
    }
    cout << n - mx << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) solve();
}
