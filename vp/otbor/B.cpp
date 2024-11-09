#include "bits/stdc++.h"
#define int int64_t
using namespace std;
const int MAXN = 300000;
int a[MAXN + 1];
int pref[MAXN + 1];
void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        a[t]++;
    }
    pref[0] = a[0];
    for (int i = 1; i <= MAXN; ++i) {
        pref[i] = pref[i - 1] + a[i];
    }
    vector<int> already(MAXN + 1, -1);
    int q;
    cin >> q;
    for (int _ = 0; _ < q; ++_) {
        int t;
        cin >> t;
        if (already[t] != -1) {
            cout << already[t] << '\n';
            continue;
        }
        int mx = LLONG_MIN;
        for (int i = 0; i <= MAXN; i += t) {
            int to = min(MAXN, i + t - 1);
            mx = max(mx, pref[to] - (i == 0 ? 0 : pref[i - 1]));
        }
        cout << mx << '\n';
        already[t] = mx;
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
