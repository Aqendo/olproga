#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

const long double PI = acosl(-1);
const long double EPS = 1e-6;

struct Point {
    int x, y;

    double dist(Point& p2) {
        return sqrt((x - p2.x) * (x - p2.x) + (y - p2.y) * (y - p2.y));
    }

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

    Point& operator*=(long double x_) {
        this->x *= x_;
        this->y *= x_;
        return *this;
    }

    Point n_vector() { return {-y, x}; }

    Point operator+(const Point& p2) { return {x + p2.x, y + p2.y}; }

    Point operator-(const Point& p2) { return {x - p2.x, y - p2.y}; }

    Point operator*(int x_) { return {x * x_, y * x_}; }

    long long vecmul(const Point& p2) const {
        return 1ll * x * p2.y - 1ll * p2.x * y;
    }

    long long scalmul(const Point& p2) const {
        return 1ll * x * p2.x + 1ll * y * p2.y;
    }

    double len() const { return sqrt(1ll * x * x + 1ll * y * y); }

    double polar_angle() {
        double atan2_result = atan2(y, x);
        if (atan2_result < 0) {
            atan2_result += 2 * PI;
        }
        return atan2_result;
    }

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
    out << p.x << " " << p.y;
    return out;
}

void solve() {
    Point A, B, C, D;
    cin >> A >> B >> C >> D;
    Point AB = B - A;
    Point CD = D - C;
    cout << AB.len() << ' ' << CD.len() << '\n';
    cout << AB + CD << '\n';
    cout << AB.scalmul(CD) << ' ' << AB.vecmul(CD) << '\n';
    cout << (double)abs(AB.vecmul(CD)) / 2 << '\n';
    cout << AB.polar_angle() << ' ' << CD.polar_angle() << '\n';
    cout << AB.angle(CD) << '\n';
    cout << AB.angle(CD) / (2 * PI) << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(9);
    solve();
}
