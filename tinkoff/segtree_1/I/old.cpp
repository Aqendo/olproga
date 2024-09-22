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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        char move;
        cin >> move;
        if (move == '+') {
            int l, r, x;
            cin >> l >> r >> x;
            l--;
            r--;
            for (int j = l; j <= r; ++j) {
                a[j] += x;
            }
        } else {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            int mx = 0;
            int now = 0;
            for (int j = l + 1; j <= r; ++j) {
                if (a[j] - a[j - 1] == 1) {
                    now += 1;
                } else {
                    mx = max(now, mx);
                    now = 0;
                }
            }
            mx = max(mx, now);
            cout << mx << '\n';
        }
    }
    return 0;
}