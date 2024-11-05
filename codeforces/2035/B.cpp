#include "bits/stdc++.h"
#define int int64_t
using namespace std;

void solve() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << -1 << '\n';
        return;
    }
    vector<vector<int>> s = {{6}, {6}};
    int even = 6;
    for (int i = 2; i < n; i += 2) {
        s[0].push_back(3);
        even += 3;
    }
    int odd = 6;
    for (int i = 3; i < n; i += 2) {
        odd += 3;
        s[1].push_back(3);
    }

    if (even - odd == 3) {
        if (s[1].size() < 2) {
            cout << -1 << '\n';
            return;
        }
        s[1][1] = 6;
    } else if (odd - even == 3) {
        if (s[0].size() < 2) {
            cout << -1 << '\n';
            return;
        }
        s[0][1] = 6;
    }
    string str = "";
    int i = 0;
    for (; i < min<int>(s[0].size(), s[1].size()); ++i) {
        str.push_back(s[0][i] + '0');
        str.push_back(s[1][i] + '0');
    }
    if (i < (int)s[1].size()) {
        str.push_back(s[1][i] + '0');
    } else if (i < (int)s[0].size()) {
        str.push_back(s[0][i] + '0');
    }
    reverse(str.begin(), str.end());
    cout << str << '\n';
}
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) solve();
}
