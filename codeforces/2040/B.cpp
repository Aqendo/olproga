#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<int> precalc;

void solve() {
    int n;
    cin >> n;
    cout << lower_bound(precalc.begin(), precalc.end(), n) - precalc.begin() + 1 << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    precalc.resize(59);
    precalc[0] = 1;
    for (int i = 1; i < 59; ++i) {
        precalc[i] = precalc[i - 1] * 2 + 2;
    }
    int t = 1;
    cin >> t;
    while (t--) solve();
}