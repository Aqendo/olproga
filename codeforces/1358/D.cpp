#include <bits/stdc++.h>
using namespace std;
#define int int64_t

int getpartially(int full, int amount) {
    return (full * (full + 1)) / 2 - (full - amount) * (full - amount + 1) / 2;
}

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(2 * n + 1);
    vector<int> pref(2 * n + 1);
    vector<int> prefarifm(2 * n + 1);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
        prefarifm[i] = prefarifm[i - 1] + a[i] * (a[i] + 1) / 2;
    }
    for (int i = n + 1; i <= 2 * n; ++i) {
        a[i] = a[i - n];
        pref[i] = pref[i - 1] + a[i];
        prefarifm[i] = prefarifm[i - 1] + a[i] * (a[i] + 1) / 2;
    }
    int from = 0;
    int s = 0;
    while (s < x) {
        from += 1;
        s += a[from];
    }
    int mx = 0;
    for (int i = from; i <= 2 * n; ++i) {
        int l = 0, r = i;
        while (l != r) {
            int m = (l + r) >> 1;
            if (pref[i] - pref[m] > x) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        int remain = x - pref[i] + pref[l];
        mx = max(mx, prefarifm[i] - prefarifm[l] + getpartially(a[l], remain));
    }
    cout << mx << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}