#include "bits/stdc++.h"

using namespace std;

// clang РЅРµ СЃС‡РёС‚Р°РµС‚ С„СѓРЅРєС†РёСЋ acosl constexpr
const long double PI = acosl(-1);

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

    Point operator+(const Point& p2) { return {x + p2.x, y + p2.y}; }

    Point operator-(const Point& p2) { return {x - p2.x, y - p2.y}; }

    Point operator*(int x_) { return {x * x_, y * x_}; }

    long long vecmul(const Point& p2) const {
        return 1ll * x * p2.y - 1ll * p2.x * y;
    }

    long long scalmul(const Point& p2) const {
        return 1ll * x * p2.x + 1ll * y * p2.y;
    }

    long double len() const { return sqrtl(1ll * x * x + 1ll * y * y); }
};

istream& operator>>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

ostream& operator<<(ostream& out, const Point& p) {
    out << '(' << p.x << "; " << p.y << ')';
    return out;
}

// segment - РѕС‚СЂРµР·РѕРє
// line - РїСЂСЏРјР°СЏ
// ray - Р»СѓС‡

long double from_point_to_segment(Point& A, Point& C, Point& D) {
    // 2. Р Р°СЃСЃС‚РѕСЏРЅРёРµ РѕС‚ С‚РѕС‡РєРё A РґРѕ РѕС‚СЂРµР·РєР° CD.
    Point CD = D - C;
    Point C__A = A - C;
    Point DC = C - D;
    Point A__D = A - D;
    bool right_poluploskost = CD.scalmul(C__A) >= 0;
    bool left_poluploskost = DC.scalmul(A__D) >= 0;
    if (left_poluploskost && right_poluploskost) {
        return abs(CD.vecmul(C__A) / CD.len());
    } else {
        return min(A.dist(C), A.dist(D));
    }
}

long double from_point_to_ray(Point& A, Point& C, Point& D) {
    // 3. Р Р°СЃСЃС‚РѕСЏРЅРёРµ РѕС‚ С‚РѕС‡РєРё A РґРѕ Р»СѓС‡Р° CD.
    Point CD = D - C;
    Point C__A = A - C;
    bool right_poluploskost = CD.scalmul(C__A) >= 0;
    if (right_poluploskost) {
        return abs(CD.vecmul(C__A) / CD.len());
    } else {
        return A.dist(C);
    }
}

long double from_point_to_line(Point& A, Point& C, Point& D) {
    Point CD = D - C;
    Point C__A = A - C;
    return abs(CD.vecmul(C__A) / CD.len());
}

bool is_intersect(int x1, int x2, int x3, int x4) {
    if (x1 > x2) {
        swap(x1, x2);
    }
    if (x3 > x4) {
        swap(x3, x4);
    }
    if (x1 > x3) {
        swap(x1, x3);
        swap(x2, x4);
    }
    return (x1 <= x3 && x3 <= x2) || (x1 <= x4 && x4 <= x2);
}

long long sign(long long a) {
    if (a > 0) return 1;
    if (a < 0) return -1;
    return 0;
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

bool is_intersect_segment_line(Point& A, Point& B, Point& C, Point& D) {
    // segment AB, line CD
    return sign((D - C).vecmul(A - C)) != sign((D - C).vecmul(B - C));
}

bool is_intersect_segment_ray(Point& A, Point& B, Point& C, Point& D) {
    // 7. Р Р°СЃСЃС‚РѕСЏРЅРёРµ РѕС‚ РѕС‚СЂРµР·РєР° AB РґРѕ Р»СѓС‡Р° CD.
    bool first = sign((A - C).vecmul(D - C)) * sign((B - C).vecmul(D - C)) < 0;
    bool second = sign((B - A).vecmul(C - A)) * sign((B - A).vecmul(D - C)) < 0;
    return first && second;
}

long double from_segment_to_ray(Point& A, Point& B, Point& C, Point& D) {
    // 7. Р Р°СЃСЃС‚РѕСЏРЅРёРµ РѕС‚ РѕС‚СЂРµР·РєР° AB РґРѕ Р»СѓС‡Р° CD.
    if (is_intersect_segment_ray(A, B, C, D)) return 0.0l;
    long double ans = LLONG_MAX;
    ans = min(ans, from_point_to_ray(A, C, D));
    ans = min(ans, from_point_to_ray(B, C, D));
    ans = min(ans, from_point_to_segment(C, A, B));
    return ans;
}

long double from_segment_to_line(Point& A, Point& B, Point& C, Point& D) {
    // 7. Р Р°СЃСЃС‚РѕСЏРЅРёРµ РѕС‚ РѕС‚СЂРµР·РєР° AB РґРѕ Р»СѓС‡Р° CD.
    if (is_intersect_segment_line(A, B, C, D)) return 0.0l;
    long double ans = LLONG_MAX;
    ans = min(ans, from_point_to_line(A, C, D));
    ans = min(ans, from_point_to_line(B, C, D));
    return ans;
}

bool is_intersect_ray_ray(Point& A, Point& B, Point& C, Point& D) {
    // AB CD
    bool first = sign((C - A).vecmul(B - A)) * sign((D - C).vecmul(B - A)) < 0;
    bool second = sign((A - C).vecmul(D - C)) * sign((B - A).vecmul(D - C)) < 0;
    return first && second;
}

long double from_ray_to_ray(Point& A, Point& B, Point& C, Point& D) {
    if (is_intersect_ray_ray(A, B, C, D)) return 0.0l;
    long double ans = LLONG_MAX;
    ans = min(ans, from_point_to_ray(A, C, D));
    ans = min(ans, from_point_to_ray(C, A, B));
    return ans;
}

bool is_intersect_ray_line(Point& A, Point& B, Point& C, Point& D) {
    return sign((A - C).vecmul(D - C)) * sign((B - A).vecmul(D - C)) < 0;
}

long double from_ray_to_line(Point& A, Point& B, Point& C, Point& D) {
    if (is_intersect_ray_line(A, B, C, D)) return 0.0l;
    return from_point_to_line(A, C, D);
}

long double from_line_to_line(Point& A, Point& B, Point& C, Point& D) {
    if ((B - A).vecmul(D - C) == 0) {
        return from_point_to_line(A, C, D);
    } else {
        return 0.0l;
    }
}

void solve() {
    Point dot;
    cin >> dot;
    int a, b, c;
    cin >> a >> b >> c;
    
}

signed main() {
    cout << fixed << setprecision(10);
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
