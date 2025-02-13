#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 5e5 + 78;

int a[N];

void solve() {
    int n;
    cin >> n;
    bool good = true;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) good &= (2 * i < a[i]) & ((n - 1 - i) * 2 < a[i]);
    cout << (good ? "YES\n" : "NO\n");
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}
