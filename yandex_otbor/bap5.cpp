#include "bits/stdc++.h"

using namespace std;
#define int long long
#define double long double
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

const double PI = acosl(-1);
const double EPS = 1e-6;
struct Point {
    int x, y;

    double dist(Point& p2) { return sqrtl((x - p2.x) * (x - p2.x) + (y - p2.y) * (y - p2.y)); }

    Point& operator+=(const Point& p2) {
        this->x += p2.x;
        this->y += p2.y;
        return *this;
    }

    Point& operator-=(const Point& p2) {
        this->x -= p2.x;
        this->y -= p2.y;
        return *this;
    }

    Point& operator*=(double x_) {
        this->x *= x_;
        this->y *= x_;
        return *this;
    }

    Point n_vector() { return {-y, x}; }

    Point operator+(const Point& p2) { return {x + p2.x, y + p2.y}; }

    Point operator-(const Point& p2) { return {x - p2.x, y - p2.y}; }

    Point operator*(int x_) { return {x * x_, y * x_}; }

    long long vecmul(const Point& p2) const { return 1ll * x * p2.y - 1ll * p2.x * y; }

    long long scalmul(const Point& p2) const { return 1ll * x * p2.x + 1ll * y * p2.y; }

    double len() const { return sqrtl(1ll * x * x + 1ll * y * y); }
    double angle(Point p2) {
        double atan2_result = atan2(vecmul(p2), scalmul(p2));
        if (atan2_result < 0) {
            atan2_result += 2 * PI;
        }
        return atan2_result;
    }
};

istream& operator>>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

ostream& operator<<(ostream& out, const Point& p) {
    out << '(' << p.x << "; " << p.y << ')';
    return out;
}
string to_string(const Point& p) {
    return "[" + to_string(p.x) + ";" + to_string(p.y) + "]";
}
bool is_lower(double a, double b) {
    return a - b < EPS;
}
void solve() {
    int n;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        if (a[mx].y < a[i].y) mx = i;
    }
    int cnt = 0;
    bool already = false;
    for (int i_ = mx + n; i_ < mx + 2 * n; ++i_) {
        Point i = a[i_ % n];
        Point before = a[(i_ + 1) % n];
        Point after = a[(i_ - 1) % n];
        if (before.y < i.y || after.y < i.y) continue;
        before -= i;
        after -= i;
        // debug(before, after);
        double angle = before.angle(after);
        // debug(angle);
        if (is_lower(PI, angle)) continue;
        // cout << format("[{};{}] maybe\n", i.x, i.y);
        if (before.y == 0 && after.y == 0) continue;
        if (before.y > 0 && after.y > 0) {
            // cout << format("[{};{}] 100%\n", i.x, i.y);
            already = false;
            cnt++;
        } else if (after.y > 0 && before.y == 0) {
            if (!already) {
                // cout << format("[{};{}] 100%\n", i.x, i.y);
                already = true;
                cnt++;
            }
        } else {
            already = false;
        }
    }
    cout << cnt;
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    solve();
}
