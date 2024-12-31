#include "bits/stdc++.h"

using namespace std;

const long double PI = acosl(-1);
const long double EPS = 1e-6;

struct Point {
    int x, y;

    long double dist(Point& p2) {
        return sqrtl((x - p2.x) * (x - p2.x) + (y - p2.y) * (y - p2.y));
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

    Point operator+(const Point& p2) const { return {x + p2.x, y + p2.y}; }

    Point operator-(const Point& p2) const { return {x - p2.x, y - p2.y}; }

    Point operator*(int x_) const { return {x * x_, y * x_}; }

    bool operator<(const Point& p2) const {
        if (y != p2.y) return y < p2.y;
        return x < p2.x;
    }

    bool operator==(const Point& p2) const { return x == p2.x && y == p2.y; }

    long long vecmul(const Point& p2) const {
        return 1ll * x * p2.y - 1ll * p2.x * y;
    }

    long long scalmul(const Point& p2) const {
        return 1ll * x * p2.x + 1ll * y * p2.y;
    }

    double len() const { return sqrt(1ll * x * x + 1ll * y * y); }

    long long squared_len() const { return 1ll * x * x + 1ll * y * y; }

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

    void normalize() {
        long double len_ = len();
        x /= len_;
        y /= len_;
    }

    friend std::string to_string(Point const& self) {
        return "(" + to_string(self.x) + ";" + to_string(self.y) + ")";
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
    out << p.x << ' ' << p.y;
    return out;
}

bool left_turn(const Point& B, const Point& O, const Point& A) {
    return (A - O).vecmul(B - O) > 0;
}

long double from_point_to_segment(Point& A, Point& C, Point& D) {
    // 2. Расстояние от точки A до отрезка CD.
    Point CD = D - C;
    Point C__A = A - C;
    Point DC = C - D;
    Point A__D = A - D;
    bool правая_полуплоскость = CD.scalmul(C__A) >= 0;
    bool левая_полуплоскость = DC.scalmul(A__D) >= 0;
    if (левая_полуплоскость && правая_полуплоскость) {
        return abs(CD.vecmul(C__A) / CD.len());
    } else {
        return min(A.dist(C), A.dist(D));
    }
}

bool is_intersect_segment_segment(Point& A, Point& B, Point& C, Point& D) {
    // AB & CD
    bool first = sign((B - A).vecmul(C - A)) != sign((B - A).vecmul(D - A));
    bool second = sign((D - C).vecmul(A - C)) != sign((D - C).vecmul(B - C));
    return first && second;
}

long double from_segment_to_segment(Point& A, Point& B, Point& C, Point& D) {
    if (is_intersect_segment_segment(A, B, C, D)) {
        return 0.0l;
    }
    long double ans = LLONG_MAX;
    ans = min(ans, from_point_to_segment(A, C, D));
    ans = min(ans, from_point_to_segment(B, C, D));
    ans = min(ans, from_point_to_segment(C, A, B));
    ans = min(ans, from_point_to_segment(D, A, B));
    return ans;
}

void solve() {
    Point a;
    cin >> a;
    cout << a.polar_angle() << endl;
}

signed main() {
    cout << setprecision(10);
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
