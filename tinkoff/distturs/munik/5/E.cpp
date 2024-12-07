#include <bits/stdc++.h>
#define int int64_t
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<array<int, 3>> statements(m);
    vector<int> role(n);
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        role[i] = k - 1;
    }
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        statements[i] = {a, b, c};
    }
    for (int mask = 0; mask < (1 << n); ++mask) {
        auto get = [&mask](int i) { return (mask >> i) & 1; };
        bool good = true;
        for (int i = 0; i < n; ++i) {
            if (role[i] < 2 && role[i] != get(i)) {
                good = false;
                break;
            }
        }
        if (!good) continue;
        for (auto& [a, b, c] : statements) {
            int k = role[a - 1];
            if (k < 2) {
                if (k != get(a - 1)) {
                    good = false;
                    break;
                }
                if (k == 0) {
                    bool correlates = get(b - 1) != 0 || get(c - 1) != 1;
                    if (!correlates) {
                        good = false;
                        break;
                    }
                }
                continue;
            }
            if (k == 2 && get(a - 1) == 0) {
                bool correlates = get(b - 1) != 0 || get(c - 1) != 1;
                if (!correlates) {
                    good = false;
                    break;
                }
            }
        }
        if (good) {
            for (int i = 0; i < n; ++i) {
                cout << get(i) + 1 << '\n';
            }
            return;
        }
    }
    cout << -1 << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
