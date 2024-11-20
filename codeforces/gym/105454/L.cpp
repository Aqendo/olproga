#include <bits/stdc++.h>
using namespace std;
#define int int64_t
void solve(int n) {
    vector<int> r(n + 5);
    r[0] = 0;
    r[1] = 1;
    r[2] = 1;
    r[3] = 0;
    r[4] = 1;
    for (int i = 5; i <= n; ++i) {
        for (int power = 0; i - (1ll << power) >= 0; ++power) {
            r[i] |= r[i - (1ll << power)] == 0;
        }
    }
    cout << r[n];
}
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    for (int i = 1; i <= 1000; ++i) {
        solve(i);
    }
}