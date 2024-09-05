#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

// void solve() {
//     // рюкзак
//     int n, S, a;
//     cin >> n >> S >> a;
//     bitset<1001> f;
//     f[0] = 1;
//     while (n--) {
//         cin >> a;
//         f |= f << a;
//     }

// }

void solve() {
    forn(k, n) forn(i, n) if (d[i][k]) d[i] |= d[k]
    // d[i][k] + d[k][j] - > d[i][j]
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
