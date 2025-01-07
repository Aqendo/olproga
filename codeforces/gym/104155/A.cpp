#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int a, b, k, m;
    cin >> a >> b >> k >> m;
    bool swapped = false;
    if (a > b) swapped = true, swap(a, b);
    vector<int> fact;
    int l = 1, r = int(sqrt(m)) + 2;
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        if (mid + m / mid > k + 1) {
            l = mid;
        } else {
            r = mid;
        }
    }
    int from = l;
    l = 1, r = int(sqrt(m)) + 2;
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        if (mid + m / mid >= k - 1) {
            l = mid;
        } else {
            r = mid;
        }
    }
    // cout << from << ' ' << r << endl;
    for (int i = from - 1; i <= r + 1; ++i) {
        if (i == 0) continue;
        if (m % i == 0) {
            fact.push_back(i);
            if (m / i != i) {
                fact.push_back(m / i);
            }
        }
    }
    pair<int, int> ans = {INT_MAX, INT_MAX};
    for (int i : fact) {
        int j = m / i;
        if (a >= i && b >= j && i - 1 + j - 1 == k) {
            if (!swapped) {
                ans = min(ans, {i - 1, j - 1});
            } else {
                ans = min(ans, {j - 1, i - 1});
            }
        }
        if (a >= j && b >= i && i - 1 + j - 1 == k) {
            if (!swapped) {
                ans = min(ans, {j - 1, i - 1});
            } else {
                ans = min(ans, {i - 1, j - 1});
            }
        }
    }
    if (ans.first == INT_MAX)
        cout << -1 << '\n';
    else
        cout << ans.first << ' ' << ans.second << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}