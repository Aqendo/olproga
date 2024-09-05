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
    if (n == 1) {
        cout << "1\n";
    } else if (n == 2) {
        cout << "-1\n";
    } else if (n % 2 == 1) {
        for (int i = n; i >= n / 2 + 2; --i) {
            cout << i << ' ';
        }
        for (int i = 1; i <= n / 2 + 1; ++i) {
            cout << i << ' ';
        }
        cout << '\n';
    } else {
        cout << "-1\n";
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) solve();
}
