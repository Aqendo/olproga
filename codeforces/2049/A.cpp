#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int firstnot = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i]) {
            firstnot = i;
            break;
        }
    }
    if (!a[firstnot]) {
        cout << "0\n";
        return;
    }
    int lastnot = n - 1;
    for (int i = n - 1; i >= 0; --i) {
        if (a[i]) {
            lastnot = i;
            break;
        }
    }
    bool have_zero = false;
    for (int i = firstnot; i <= lastnot; ++i) {
        if (!a[i]) {
            cout << 2 << '\n';
            return;
        }
    }
    cout << 1 << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}