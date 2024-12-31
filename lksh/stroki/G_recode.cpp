#include "bits/stdc++.h"

using namespace std;

void solve() {
    string s = "#";
    char c;
    int n = 0;
    while (cin >> c) {
        // debugging purposes
        if (c == '$') break;
        n++;
        s += c;
        s += '#';
    }
    int l = 0, r = 0;
    vector<int> z(2 * n + 1);
    z[0] = 1;
    for (int i = 1; i < 2 * n + 1; ++i) {
        if (i <= r) {
            int from = l + (r - i);
            z[i] = min({from - l + 1, z[from], r - i + 1});
        }
        while (i - z[i] >= 0 && i + z[i] < 2 * n + 1 && s[i - z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i - z[i] + 1, r = i + z[i] - 1;
        }
    }
    int sum = 0;
    for (int i : z) sum += i;
    cout << (sum - n - 1) / 2 - n << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}