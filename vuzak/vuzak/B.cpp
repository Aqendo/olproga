#include <bits/stdc++.h>
using namespace std;
#define int int64_t
int s, k;
__int128 get(__int128 n) {
    return ((__int128)2 + (__int128)k * (__int128)(n - 1)) * (__int128)n / (__int128)2;
}
void solve() {
    cin >> s >> k;
    // for (int i = 1; i <= 10; ++i) {
    //     cout << (int)get(i) << endl;
    // }
    // exit(0);
    __int128 l = 1, r = s + 4;
    __int128_t ss = s;
    while (r - l > 1) {
        __int128 m = (l + r) >> 1;
        if (get(m) <= ss) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << (int)l << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}