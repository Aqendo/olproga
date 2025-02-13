#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define answer(x)        \
    cout << (x) << '\n'; \
    return;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int r;
    cin >> r;
    if (n == 2) {
        int res = a[0] <= a[1];
        if (res == r) {
            answer(0);
        }
        answer(-1);
    }
    if (r == 1) {
        if (a.back() == 1) {
            answer(0);
        }
        if (a[a.size() - 1] == 0 && a[a.size() - 2] == 0) {
            cout << n - 1 << ' ' << n << '\n';
            return;
        }
        if (a[a.size() - 2] == 1 && a[a.size() - 1] == 0) {
            int res = 1;
            for (int i = 0; i < (int)a.size() - 2; ++i) {
                res = (res <= a[i]);
                if (res == 0) {
                    cout << i + 2 << ' ' << n << '\n';
                    return;
                }
            }
            answer(-1);
        }
        assert(false);
    }
    if (a.back() == 1) {
        answer(-1);
    }
    if (a[a.size() - 2] == 1 && a[a.size() - 1] == 0) {
        answer(0);
    }
    if (a[a.size() - 3] == 1 && a[a.size() - 2] == 0 && a[a.size() - 1] == 0) {
        if (a.size() == 3) {
            cout << -1 << '\n';
            return;
        }
        int res = 1;
        for (int i = 0; i < (int)a.size() - 3; ++i) {
            res = (res <= a[i]);
            if (res == 0) {
                cout << i + 2 << ' ' << n - 1 << '\n';
                return;
            }
        }
        answer(-1);
    }
    if (a[a.size() - 3] == 0 && a[a.size() - 2] == 0 && a[a.size() - 1] == 0) {
        cout << n - 2 << ' ' << n - 1 << '\n';
        return;
    }
    assert(false);
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
