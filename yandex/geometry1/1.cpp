#include <bits/stdc++.h>
using namespace std;

struct pt {
    int x, y;
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
    pt operator*(const pt &r) const {
        return {
            x * r.x,
            y * r.y};
    }
    pt operator/(const pt &r) const {
        return {
            x / r.x,
            y / r.y};
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
    pt &operator*=(int mul) {
        x *= mul;
        y *= mul;
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
    int scalmul(const pt &r) {
        return x * r.x + y * r.y;
    }
    int vecmul(const pt &r) {
        return x * r.y - y * r.x;
    }
    double len() {
        return sqrt(squaredlen());
    }
    int squaredlen() {
        return scalmul(*this);
    }
    double dist(const pt &r) {
        return sqrt((r.x - x) * (r.x - x) + (r.y - y) * (r.y - y));
    }
};

istream &operator>>(istream &in, pt &r) {
    in >> r.x >> r.y;
    return in;
}
ostream &operator<<(ostream &out, pt &r) {
    out << '(' << r.x << ';' << r.y << ')';
    return out;
}

void solve() {
    int n;
    cin >> n;
    vector<pt> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i];
    }
    double mx = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            mx = max(mx, points[i].dist(points[j]));
        }
    }
    cout << mx << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << setprecision(10000);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
