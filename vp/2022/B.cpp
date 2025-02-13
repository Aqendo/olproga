#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 3e5 + 78;

pair<int, int> dots[N];
int pmny[N], pmxy[N];
int smny[N], smxy[N];

int w, h, n;

bool f(int size) {
    for (int i = 1; i <= n; ++i) {
        if (dots[i].second == dots[i - 1].second) {
            continue;
        }
        int mx = pmxy[i - 1];
        int mn = pmny[i - 1];
        auto it = lower_bound(dots + i, dots + n + 1, dots[i].second + size, [](auto &l, int val) {
            return l.second < val;
        });
        int index = it - dots;
        mx = max(mx, smxy[index]);
        mn = min(mn, smny[index]);
        if (mx - mn + 1 <= size) {
            return true;
        }
    }
    return false;
}

void solve() {
    cin >> w >> h >> n;
    dots[0] = {INT_MIN, INT_MIN};
    pmny[0] = smny[n + 1] = INT_MAX;
    pmxy[0] = smxy[n + 1] = INT_MIN;
    for (int i = 1; i <= n; ++i) {
        cin >> dots[i].first >> dots[i].second;
    }
    sort(dots + 1, dots + n + 1, [](auto &l, auto &r) {
        return l.second < r.second;
    });
    for (int i = 1; i <= n; ++i) {
        pmny[i] = min(pmny[i - 1], dots[i].first);
        pmxy[i] = max(pmxy[i - 1], dots[i].first);
    }
    for (int i = n; i >= 1; --i) {
        smny[i] = min(smny[i + 1], dots[i].first);
        smxy[i] = max(smxy[i + 1], dots[i].first);
    }
    int l = 0, r = min(w, h);
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        if (f(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
