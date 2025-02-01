#pragma GCC optimize("O3")
#include <bits/allocator.h>
#include <bits/stdc++.h>
using namespace std;

int min(int a, int b) { return a < b ? a : b; }

#pragma GCC target("popcnt,avx2")
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n), b(m);
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    vector<int> masks_and(1 << m, -1);
    for (int mask = 0; mask < (1 << m); ++mask) {
        for (int bit = 0; bit < m; ++bit) {
            if (mask >> bit & 1) {
                if (masks_and[mask] == -1) {
                    masks_and[mask] = b[bit];
                } else {
                    masks_and[mask] &= b[bit];
                }
            }
        }
    }
    vector<int> possibilities;
    possibilities.reserve(n * m);
    for (int i = 0; i < n; ++i) {
        vector<int> mn(m + 1, a[i]);
        int el = a[i];
        for (int mask = 0; mask < (1ll << m); ++mask) {
            mn[__builtin_popcount(mask)] = min(mn[__builtin_popcount(mask)], el & masks_and[mask]);
        }
        for (int j = 1; j < m + 1; ++j) {
            possibilities.push_back(abs(mn[j] - mn[j - 1]));
        }
    }
    sort(possibilities.rbegin(), possibilities.rend());
    sum -= accumulate(possibilities.begin(), possibilities.begin() + k, 0ll);
    cout << sum << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}