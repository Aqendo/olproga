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
const int MAXN = 1e5 + 1;
int cnt[MAXN];

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        cnt[t]++;
    }
    int total = 0;
    for (int i : cnt) {
        total += i / 2;
    }
    cout << (total % 2 == 0) + 1;
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
