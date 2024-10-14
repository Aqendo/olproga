#include "bits/stdc++.h"
using namespace std;
# define int long long
# ifdef SEREGA
#include "/home/ser/olproga/debug.h"
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
# endif

# ifndef SEREGA
# define printf(...)
# define debug(...)
# endif

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> pref(n);
    for (int i = 1; i < n; ++i) {
        int cur = pref[i - 1];
        while (s[cur] != s[i] && cur > 0) {
            cur = pref[cur - 1];
        }
        if (s[i] == s[cur]) {
            pref[i] = cur + 1;
        }
    }
    for (int i : pref) {
        cout << i << ' ';
    }
}

signed main() {
# ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
# endif
    solve();
}
