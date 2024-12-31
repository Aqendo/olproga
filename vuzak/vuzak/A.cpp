#include <bits/stdc++.h>
using namespace std;
int arr[3] = {3, 5, 7};
void solve() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << 4;
    } else if (n == 2) {
        cout << 5;
    } else if (n == 3) {
        cout << 7;
    } else if (n % 3 == 0) {
        cout << (n / 3 * 7);
    } else {
        cout << (n / 3 * 7) + arr[n % 3 - 1];
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}