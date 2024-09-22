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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = 0;
    }
    for (int i = 0; i < m; ++i) {
        int move;
        cin >> move;
        if (move == 1) {
            int l, r, v;
            cin >> l >> r >> v;
            for (int ii = l; ii < r; ++ii) {
                a[ii] = v;
            }
            debug(a);
        } else if (move == 2) {
            int l, r, v;
            cin >> l >> r >> v;
            for (int ii = l; ii < r; ++ii) {
                a[ii] += v;
            }

            debug(a);
        } else {
            int l, r;
            cin >> l >> r;
            int s = 0;
            for (int ii = l; ii < r; ++ii) {
                s += a[ii];
            }

            debug(a);
            cout << s << '\n';
        }
    }
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
