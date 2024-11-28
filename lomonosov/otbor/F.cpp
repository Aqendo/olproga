#include <bits/stdc++.h>
using namespace std;
#define int int64_t
int sizes[64];

void precalc() {
    sizes[1] = 1;
    for (int i = 1; i < 64; ++i) {
        sizes[i] = sizes[i - 1] * 2 + 1;
    }
}
vector<string> order = {"В", "Д", "К", "Т"};
void solve() {
    int n, k;
    cin >> n >> k;
    k++;
    int offset = 0;
    for (int i = n; i >= 2; --i) {
        // cout << i << ' ' << sizes[i] << ' ' << k << endl;
        int sz = sizes[i];
        if (k == sz / 2 + 1) {
            cout << order[(3 + offset) % 4] << endl;
            return;
        }
        if (k > sz / 2 + 1) {
            k = sz - k + 1;
            offset++;
        }
    }
    cout << order[offset % 4] << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    precalc();
    int t = 1;
    // cin >> t;
    while (t--) solve();
}