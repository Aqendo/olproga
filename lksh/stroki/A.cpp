#include "bits/stdc++.h"
#include <string>

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

void solve() {
    string s;
    cin >> s;
    vector<int> prefix(s.size());
    for (int i = 1; i < s.size(); ++i) {
        int k = prefix[i - 1];
        while (k > 0 && s[i] != s[k]) {
            k = prefix[k - 1];
        }
        if (s[k] == s[i]) {
            k++;
        }
        prefix[i] = k;
    }
    for (int i : prefix) {
        cout << i << ' ';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}