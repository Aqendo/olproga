#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n, d;
    cin >> n >> d;
    cout << ((n / 2) + d - 1) / d << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}
