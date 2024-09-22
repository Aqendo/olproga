#include "bits/stdc++.h"
using namespace std;
#define int long long
#define double long double
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

#ifndef SEREGA
#define printf(...)
#define debug(...)
#endif
void solve() {
    int n, m;
    cin >> n >> m;
    int mx = INT_MIN;
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int t;
            cin >> t;
            if (t > mx) {
                mx = t;
                ans = {i};
            } else if (t == mx) {
                if (ans.empty() || ans.back() != i) {
                    ans.push_back(i);
                }
            }
        }
    }
    cout << ans.size() << '\n';
    for (int i : ans) {
        cout << i << ' ';
    }
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
