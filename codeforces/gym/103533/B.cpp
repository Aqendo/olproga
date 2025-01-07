#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define double long double
const double EPS = 1e-13;
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    double mn = INT_MAX;
    double mx = INT_MIN;
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        mn = min(mn, (double)a[0] / b[i]);
        mx = max(mx, (double)a[n - 1] / b[i]);
    }
    auto f = [&a, &b, &n](double value) -> int {
        int answer = 0;
        for (int osn : b) {
            int l = 0, r = n;
            while (r - l > 1) {
                int m = (l + r) >> 1;
                if ((double)a[m] / osn <= value) {
                    l = m;
                } else {
                    r = m;
                }
            }
            if ((double)a[l] / osn <= value) {
                answer += l + 1;
            }
        }
        return answer;
    };
    auto get_ans = [&a, &b, &n](double value) -> pair<int, int> {
        for (int osn : b) {
            int l = 0, r = n;
            while (r - l > 1) {
                int m = (l + r) >> 1;
                if ((double)a[m] / osn <= value + 2 * EPS) {
                    l = m;
                } else {
                    r = m;
                }
            }
            for (int i = max<int>(0, l - 1); i <= min<int>(n - 1, l + 1); ++i) {
                if (abs((double)a[l] / osn - value) <= EPS) {
                    return {a[l], osn};
                }
            }
        }
        return {-1, -1};
    };
    while (q--) {
        int t;
        cin >> t;
        double l = mn, r = mx + 0.001;
        while (r - l > EPS) {
            double m = (l + r) / 2;
            if (m == l) break;
            if (f(m) < t) {
                l = m;
            } else {
                r = m;
            }
        }
        auto ans = get_ans(r);
        auto gc = __gcd(ans.first, ans.second);
        cout << ans.first / gc << ' ' << ans.second / gc << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}