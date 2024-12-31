#include <bits/stdc++.h>
using namespace std;

struct pt {
    double x, y;
    pt operator+(const pt &r) const {
        return {
            x + r.x,
            y + r.y};
    }
    pt operator-(const pt &r) const {
        return {
            x - r.x,
            y - r.y};
    }
    pt operator*(int mul) const {
        return {
            x * mul,
            y * mul};
    }
    pt operator*(double mul) const {
        return {
            x * mul,
            y * mul};
    }
    pt operator/(int mul) const {
        return {
            x / mul,
            y / mul};
    }
    pt operator/(double mul) const {
        return {
            x / mul,
            y / mul};
    }

    pt &operator+=(const pt &r) {
        x += r.x;
        y += r.y;
        return *this;
    }
    pt &operator-=(const pt &r) {
        x -= r.x;
        y -= r.y;
        return *this;
    }
    pt &operator*=(double mul) {
        x *= mul;
        y *= mul;
        return *this;
    }
    pt &operator*=(int mul) {
        x *= mul;
        y *= mul;
        return *this;
    }
    pt &operator/=(double mul) {
        x /= mul;
        y /= mul;
        return *this;
    }
    pt &operator/=(int mul) {
        x /= mul;
        y /= mul;
        return *this;
    }
    bool operator==(const pt &r) {
        return x == r.x && y == r.y;
    }
    double scalmul(const pt &r) {
        return x * r.x + y * r.y;
    }
    double vecmul(const pt &r) {
        return x * r.y - y * r.x;
    }
    double len() {
        return sqrt(squaredlen());
    }
    double squaredlen() {
        return scalmul(*this);
    }
    double dist(const pt &r) {
        return sqrt((r.x - x) * (r.x - x) + (r.y - y) * (r.y - y));
    }
    pt normalize() {
        double ln = len();
        return {
            x / ln, y / ln};
    }
};

istream &operator>>(istream &in, pt &r) {
    in >> r.x >> r.y;
    return in;
}
ostream &operator<<(ostream &out, const pt &r) {
    out << r.x << ' ' << r.y;
    return out;
}

void solve() {
    pt x, y, z, w;
    cin >> x >> y >> z >> w;
    pt a = y - x;
    pt b = w - z;
    a = a.normalize();
    b = b.normalize();
    if (a == b) {
        
    } 
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << setprecision(10);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
