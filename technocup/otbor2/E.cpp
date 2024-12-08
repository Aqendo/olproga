#include <bits/stdc++.h>
#define int int64_t
#define double long double
using namespace std;

struct pt {
    double x, y;
    double len() {
        return sqrt(x * x + y * y);
    }
    void setlen(double len_) {
        double prev_ = len();
        x /= prev_;
        y /= prev_;
        x *= len_;
        y *= len_;
    }
    pt operator-(const pt &r) {
        return {
            x - r.x,
            y - r.y};
    }
    pt operator+(const pt &r) {
        return {
            r.x + x,
            r.y + y};
    }
};

void solve() {
    int n, t;
    cin >> n >> t;
    vector<pt> dots(n);
    vector<int> times(t);
    for (int i = 0; i < n; ++i) {
        cin >> dots[i].x >> dots[i].y;
    }
    for (int i = n - 2; i >= 0; --i) {
        dots.push_back(dots[i]);
    }
    const double EPS = 1e-8;
    vector<double> pref(dots.size());
    for (int i = 0; i <= (int)dots.size() - 2; ++i) {
        if (i != 0) pref[i + 1] = pref[i];
        pref[i + 1] += (dots[i + 1] - dots[i]).len();
    }
    double all = pref.back();
    // for (auto u : pref) cout << u << ' ';
    // cout << endl;
    for (int i = 1; i <= t; ++i) {
        double x;
        cin >> x;
        x = fmod(x, all);
        // cout << "x " << x << endl;
        auto it = upper_bound(pref.begin(), pref.end(), x);
        int index = it - pref.begin() - 1;
        // cout << it - pref.begin() << ' ' << pref[0] << endl;
        x -= pref[index];
        pt vec = dots[index + 1] - dots[index];
        vec.setlen(x);
        pt ans = dots[index] + vec;
        cout << ans.x << ' ' << ans.y << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << setprecision(10);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
