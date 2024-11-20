#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n;
    cin >> n;
    vector<int> a;
    int prod = 1;
    for (int i = 1; i < n; ++i) {
        if (gcd(i, n) == 1) a.push_back(i), prod *= i, prod %= n;
    }
    if (prod != 1) {
        a.erase(lower_bound(a.begin(), a.end(), prod));
    }
    cout << a.size() << endl;
    for (int i : a) cout << i << ' ';
    cout << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}