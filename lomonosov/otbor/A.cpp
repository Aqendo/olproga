#include <bits/stdc++.h>
using namespace std;
#define int int64_t
const int MAXA = 1004;

int hmneed[MAXA];

void solve() {
    for (int i = 1; i < MAXA; ++i) {
        int number = i;
        int cnt = 0;
        while (number != 1) {
            cnt++;
            if (number & 1) {
                number = 3 * number + 1;
            } else {
                number >>= 1;
            }
        }
        hmneed[i] = cnt;
    }
    int n;
    cin >> n;
    vector<int> a(n);
    int mn = INT_MAX;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        a[i] = hmneed[t];
        mn = min(mn, a[i]);
    }
    int mx = INT_MIN;
    for (int i = 0; i < n; ++i) {
        mx = max(mx, a[i]);
        a[i] -= mn;
        if (a[i] % 3 != 0) {
            cout << "-1\n";
            return;
        }
    }
    cout << mx << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}