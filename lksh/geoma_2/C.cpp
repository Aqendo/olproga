#include "bits/stdc++.h"

using namespace std;

const long double TWO_PI = 2.0l * acosl(-1);
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
            atan2_result += TWO_PI;
        }
        return atan2_result;
    }

    double angle(Point p2) { return atan2(vecmul(p2), scalmul(p2)); }

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

bool is_intersect_point_segment(Point C, Point A, Point B) {
    return (C - A).scalmul(B - A) >= 0 && (C - B).scalmul(A - B) >= 0 &&
           (C - A).vecmul(B - A) == 0;
}

bool is_within_angle(Point P, Point A, Point B) {
    bool answer = true;
    answer &= sign((B).vecmul(A)) * sign((P).vecmul(A)) >= 0;
    answer &= sign((A).vecmul(B)) * sign((P).vecmul(B)) >= 0;
    return answer;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i];
    }
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        Point point;
        cin >> point;
        int l = 2, r = n - 1;
        while (l != r) {
            int mid = (l + r) >> 1;
            long long res_up =
                (point - points[0]).vecmul(points[mid] - points[0]);
            if (sign(res_up) == -1) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        Point A = points[0];
        Point B = points[l];
        Point C = points[l - 1];
        Point P = point;
        bool first = is_within_angle(P - C, A - C, B - C);
        bool second = is_within_angle(P - A, B - A, C - A);
        cnt += first && second;
    }
    cout << (cnt >= k ? "YES" : "NO") << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}