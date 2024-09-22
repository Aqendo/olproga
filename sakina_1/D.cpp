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
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& i : a) cin >> i;
    int t;
    cin >> t;
    int l = 0, r = n;
    while (r - l > 1) {
        int m = (l + r) >> 1;
        if (a[m] >= t) {
            l = m;
        } else {
            r = m;
        }
    }
    if (a[l] < t) l--;
    cout << l + 2;
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
