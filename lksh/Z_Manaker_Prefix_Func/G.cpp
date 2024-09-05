#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

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
    vector<int> z(s.size());
    for (int i = 0; i <= s.size(); ++i) {
        z[i] = min(max(0, r - i), z[l + r - i]);
        while (z[i] <= i && i + z[i] < s.size() && s[i - z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (z[i] + i > r) {
            l = i - z[i];
            r = i + z[i];
        }
    }
    long long ans = 0;
    for (int i : z) {
        ans += i;
    }
    cout << (ans - n - 1) / 2 - n;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
