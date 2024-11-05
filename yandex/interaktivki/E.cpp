#include "bits/stdc++.h"
using namespace std;
const long double EPS = 1e-7;
vector<array<long double, 3>> dots;
long double mn = 1e18;
long double x_ans = 0, y_ans = 0, z_ans = 0;
long double f3(long double x, long double y, long double z) {
    long double local_mx = -1e18;
    for (int i = 0; i < (int)dots.size(); ++i) {
        long double sqrx = (x - dots[i][0]) * (x - dots[i][0]);
        long double sqry = (y - dots[i][1]) * (y - dots[i][1]);
        long double sqrz = (z - dots[i][2]) * (z - dots[i][2]);
        local_mx = max(local_mx, sqrx + sqry + sqrz);
    }
    if (local_mx < mn) {
        x_ans = x;
        y_ans = y;
        z_ans = z;
        mn = local_mx;
    }
    return local_mx;
}

long double f2(long double x, long double y) {
    long double l = -1002;
    long double r = 1002;
    long double last = 0;
    for (int i = 0; i < 130; ++i) {
        long double m1 = l + (r - l) / 3;
        long double m2 = r - (r - l) / 3;
        last = f3(x, y, m1);
        if (last < f3(x, y, m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    return last;
}

long double f1(long double x) {
    long double l = -1002;
    long double r = 1002;
    long double last = 0;
    for (int i = 0; i < 130; ++i) {
        long double m1 = l + (r - l) / 3;
        long double m2 = r - (r - l) / 3;
        last = f2(x, m1);
        if (last < f2(x, m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    return last;
}

void solve() {
    int n;
    cin >> n;
    dots.resize(n);
    for (int i = 0; i < n; ++i) {
        long double x, y, z;
        cin >> x >> y >> z;
        dots[i] = {x, y, z};
    }
    long double l = -1002;
    long double r = 1002;
    for (int i = 0; i < 130; ++i) {
        long double m1 = l + (r - l) / 3;
        long double m2 = r - (r - l) / 3;
        if (f1(m1) < f1(m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    cout << x_ans << ' ' << y_ans << ' ' << z_ans << '\n';
}

int main() {
    cout << setprecision(12);
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
