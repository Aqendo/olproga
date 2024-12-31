#include "bits/stdc++.h"
using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> z(n);
    z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i, r = i + z[i] - 1;
        }
    }
    for (int i : z) {
        cout << i << ' ';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
