#include "bits/stdc++.h"
using namespace std;
#define int long long
#ifdef SEREGA
#include "/home/ser/olproga/debug.h"
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

#ifndef SEREGA
#define printf(...)
#define debug(...)
#endif

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &i : a) cin >> i;
    sort(a.begin(), a.end());
    int sum = a[0] + a[n - 1];
    for (int i = 0; i < n; ++i) {
        if (a[i] + a[n - 1 - i] != sum) {
            cout << "NO\n";
            return;
        }
    }
    cout << "SI\n";
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int t; cin >> t;
    while (t--)
        solve();
}
