#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    if (n % 33) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
}
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}