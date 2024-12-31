#include "bits/stdc++.h"

using namespace std;

const long double PI = acosl(-1);
const long double EPS = 1e-6;

struct Point {
    long double x, y;

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

long double from_point_to_line(Point& A, Point& C, Point& D) {
    Point CD = D - C;
    Point C__A = A - C;
    return abs(CD.vecmul(C__A) / CD.len());
}

void solve() {
    Point P;
    cin >> P;
    long double A, B, C;
    cin >> A >> B >> C;
    Point first, second;
    if (B != 0) {
        first = {0, -C / B};
    } else {
        first = {-C / A, 0};
    }
    second = first;
    second += {-B, A};
    double result = from_point_to_line(P, first, second);
    if (abs(result) <= 0.0000001) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

signed main() {
    cout << setprecision(10);
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
