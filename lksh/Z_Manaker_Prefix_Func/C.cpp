#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> Z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        Z[i] = min(max(0, r - i), Z[i - l]);
        while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]]) {
            Z[i]++;
        }
        if (i + Z[i] > r) {
            r = i + Z[i];
            l = i;
        }
    }
    for (int i = 1; i < n; ++i) {
        if (i + Z[i] == n) {
            cout << i << ' ';
            return;
        }
    }
    cout << n << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
