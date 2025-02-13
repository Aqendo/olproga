#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n;
    cin >> n;
    map<int, int> a;
    map<int, int> b;

    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        a[t]++;
    }
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        b[t]++;
    }
    vector<array<int, 3>> diffs_a, diffs_b;

    for (auto [u, v] : a) {
        if (!b.contains(u)) {
            diffs_a.push_back({u, v, 0});
        } else if (b[u] != v) {
            diffs_a.push_back({u, v, b[u]});
        }
    }
    for (auto [u, v] : b) {
        if (!a.contains(u)) {
            diffs_b.push_back({u, v, 0});
        } else if (a[u] != v) {
            diffs_b.push_back({u, v, a[u]});
        }
    }
    if (diffs_a.empty() && diffs_b.empty()) {
        cout << 0 << '\n';
        return;
    }
    if (diffs_a.size() == diffs_b.size() && diffs_a.size() == 2 && diffs_a[0][0] == diffs_b[0][0] && diffs_a[1][0] == diffs_b[1][0]) {
        cout << 1 << '\n';
        return;
    }
    if (diffs_a.size() == diffs_b.size() && diffs_a.size() == 1 && diffs_a[0][1] == diffs_b[0][1]) {
        cout << 1 << '\n';
        return;
    }
    cout << -1 << '\n';
}
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
