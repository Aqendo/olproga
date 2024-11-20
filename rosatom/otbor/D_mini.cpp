#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    vector<int> a = {1, 2, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 8, 9, 10};
    int n = a.size();
    auto get = [&](int k) -> int {
        int limit = 0;
        int l = 0, r = 10000;
        while (r - l > 1) {
            int mid = (l + r) >> 1;
            int index = upper_bound(a.begin(), a.end(), mid) - a.begin() - 1;
            if (index + 1 < k) {
                l = mid;
            } else {
                r = mid;
            }
        }
        return r;
    };
    for (int i = 0; i < n; ++i) {
        bool good = get(i + 1) == a[i];
        if (!good) {
            cout << "NOT GOOD\n" << i << '\n';
            return;
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}