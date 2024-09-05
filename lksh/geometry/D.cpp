#include <iomanip>
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

    bool operator==(const Point& p2) const { return x == p2.x && y == p2.y; }

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

long long sign(long long a) {
    if (a > 0) return 1;
    if (a < 0) return -1;
    return 0;
}

istream& operator>>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

ostream& operator<<(ostream& out, const Point& p) {
    out << p.x << " " << p.y;
    return out;
}

long double from_point_to_segment(Point& A, Point& C, Point& D) {
    // 2. Расстояние от точки A до отрезка CD.
    Point CD = D - C;
    Point C__A = A - C;
    Point DC = C - D;
    Point A__D = A - D;
    bool right_poluploskost = CD.scalmul(C__A) >= 0;
    bool left_poluploskost = DC.scalmul(A__D) >= 0;
    if (left_poluploskost && right_poluploskost) {
        return abs((long double)CD.vecmul(C__A) / CD.len());
    } else {
        return min(A.dist(C), A.dist(D));
    }
}

void solve() {
    Point A, B, C;
    int L;
    cin >> A >> B >> C >> L;
    if (A == B) {
        cout << max(0.0, B.dist(C) - L) << '\n';
        cout << max(0.0, B.dist(C) - L) << '\n';
        return;
    }
    cout << max<long double>(0.0l, from_point_to_segment(C, A, B) - L) << '\n';
    cout << max(0.0l, max<long double>(A.dist(C), B.dist(C)) - L) << '\n';
}

signed main() {
    cout << fixed << setprecision(10);
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
