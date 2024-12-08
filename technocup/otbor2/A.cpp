#include <bits/stdc++.h>
#define int int64_t
using namespace std;

void solve() {
    int n;
    string s;
    cin >> n >> s;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += s[i] - '0';
    }
    if (sum % 3 != 0) {
        cout << -1 << endl;
        return;
    }
    if ((s.back() - '0') % 2 == 0) {
        cout << 0 << endl;
    } else {
        int pos = -1;
        for (int i = (int)s.size() - 1; i >= 0; --i) {
            if ((s[i] - '0') % 2 == 0) {
                pos = i;
                break;
            }
        }
        if (pos == -1) {
            cout << -1 << endl;
            return;
        }
        cout << s.size() - pos - 1  << endl;
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
