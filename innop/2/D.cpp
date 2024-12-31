#include <bits/stdc++.h>
using namespace std;
#define int int64_t
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    int mx = INT_MIN;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    int q;
    cin >> q;
    vector<int> temp;
    vector<pair<int, int>> moves(q);
    bool has5 = false;
    for (int i = 0; i < q; ++i) {
        int move, x;
        cin >> move >> x;
        moves[i] = {move, x};
        if (move == 5) has5 = true;
    }
    if (has5) {
        for (int i = 0; i < q; ++i) {
            auto [move, x] = moves[i];
            if (move == 1) {
                for (int &i : a) {
                    i &= x;
                }
            } else if (move == 2) {
                for (int &i : a) {
                    i |= x;
                }
            } else if (move == 3) {
                for (int &i : a) {
                    i ^= x;
                }
            } else if (move == 4) {
                cout << a[x - 1] << '\n';
            } else {
                vector t = a;
                sort(t.begin(), t.end());
                cout << t[x - 1] << '\n';
            }
        }
        return;
    } else {
        vector<int> ones(32, 1);
        vector<int> zeroes(32, 0);
        for (int i = 0; i < q; ++i) {
            auto [move, x] = moves[i];
            if (move == 1) {
                for (int i = 0; i < 32; ++i) {
                    ones[i] &= x >> i & 1;
                    zeroes[i] &= x >> i & 1;
                }
            } else if (move == 2) {
                for (int i = 0; i < 32; ++i) {
                    ones[i] |= x >> i & 1;
                    zeroes[i] |= x >> i & 1;
                }
            } else if (move == 3) {
                for (int i = 0; i < 32; ++i) {
                    ones[i] ^= x >> i & 1;
                    zeroes[i] ^= x >> i & 1;
                }
            } else if (move == 4) {
                int res = 0;
                for (int bit = 0; bit < 32; ++bit) {
                    if (a[x - 1] >> bit & 1) {
                        if (ones[bit])
                            res += (1ll << bit);
                    } else {
                        if (zeroes[bit])
                            res += (1ll << bit);
                    }
                }
                cout << res << '\n';
            }
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}