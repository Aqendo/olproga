#include <bits/stdc++.h>
#define int int64_t
using namespace std;
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> pref(3 * n + 3);
    vector<int> suff(3 * n + 42);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (i != 0) {
            pref[i] = pref[i - 1];
        }
        pref[i] += a[i];
    }
    for (int c = 0; c < 2; ++c) {
        for (int i = 0; i < n; ++i) {
            pref[a.size()] = pref[a.size() - 1] + a[i];
            a.push_back(a[i]);
        }
    }
    for (int i = (int)a.size() - 1; i >= 0; --i) {
        suff[i] = suff[i + 1] + a[i];
    }
    for (int start = n; start < n + n; ++start) {
        int now = 0;
        for (int offset = 1; offset <= n / 2; ++offset) {
            now += offset * a[start - offset];
            if ((start - offset) % n == (start + offset) % n) continue;
            now += offset * a[start + offset];
        }
        cout << now << endl;
    }
    cout << endl;

    int now = 0;
    for (int offset = 1; offset <= n / 2; ++offset) {
        now += offset * a[n - offset];
        if ((n - offset) % n == (n + offset) % n) continue;
        now += offset * a[n + offset];
    }
    cout << now << endl;
    int answer = now;
    int max_offset = n / 2;
    for (int start = n + 1; start < n + n; ++start) {
        now -= (max_offset)*a[start - 1 - max_offset];
        now += pref[start - 2] - pref[start - 1 - max_offset];
        if ((start - max_offset) % n != (start + max_offset) % n) {
            assert(false);
        }
        now -= a[start];
        now += a[start - 1];
        now -= suff[start + 1] - suff[start + max_offset - 1];
        now += a[start + max_offset - 1] * (max_offset - 1);
        answer = min(answer, now);
        cout << now << endl;
    }
    cout << answer << endl;
}
/*
98
120
114
118
96
96


102
98
120
114
118
96


*/