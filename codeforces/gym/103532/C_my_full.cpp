#pragma GCC optimize("Ofast")
#include <bits/allocator.h>
#pragma GCC target("avx2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;

#define M_PI 3.14159265358979323846

struct pt {
    int x, y;
    int slen() const {
        return x * x + y * y;
    }
    int sdist(const pt &r) const {
        return (x - r.x) * (x - r.x) + (y - r.y) * (y - r.y);
    }
    pt operator-(const pt &r) const {
        return {
            x - r.x,
            y - r.y};
    }
    pt operator+(const pt &r) const {
        return {
            x + r.x,
            y + r.y};
    }
    pt operator*(int mult) const {
        return {
            x * mult,
            y * mult};
    }
    pt &operator-=(const pt &r) {
        x -= r.x;
        y -= r.y;
        return *this;
    }
    pt &operator+=(const pt &r) {
        x += r.x;
        y += r.y;
        return *this;
    }
    pt &operator*=(int mult) {
        x *= mult;
        y *= mult;
        return *this;
    }
    long long scal(const pt &r) const {
        return 1ll * x * r.x + 1ll * y * r.y;
    }
    long long vec(const pt &r) const {
        return 1ll * x * r.y - 1ll * r.x * y;
    }
    double getAngle(const pt &r) const {
        return fabs(atan2(vec(r), scal(r)));
    }
    double getAngleDegrees(const pt &r) const {
        return getAngle(r) * 180 / M_PI;
    }
};
istream &operator>>(istream &in, pt &r) {
    in >> r.x >> r.y;
    return in;
}
ostream &operator<<(ostream &out, pt &r) {
    out << "(" << r.x << ";" << r.y << ")";
    return out;
}

pt a[30][3];
double an[30][3];
int n;

set<array<int, 4>> answer;

array<int, 4> arr;
inline bool notSame(int i, int j, int k, int m) {
    if (arr[0] == arr[1] || arr[1] == arr[2] || arr[2] == arr[3] || arr[3] == arr[4] || answer.contains(arr)) return false;
    return true;
}

inline bool isPI(double res) {
    return fabs(res - M_PI) < 1e-12;
}
inline int subm(int x) {
    return x < 0 ? x + 3 : x;
}
inline int addm(int x) {
    return x >= 3 ? x - 3 : x;
}
array<array<pt, 3>, 4> tr;
array<array<double, 3>, 4> tra;

double angle(int i, int corner) {
    return (tr[i][corner == 0 ? 2 : corner - 1] - tr[i][corner]).getAngle(tr[i][corner == 2 ? 0 : corner + 1] - tr[i][corner]);
}

bool check() {
    bool upper = isPI(tra[0][1] + tra[1][2] + tra[2][2]);
    bool left = isPI(tra[0][0] + tra[1][0] + tra[3][2]);
    bool right = isPI(tra[2][0] + tra[1][1] + tra[3][1]);
    bool angles = upper && left && right;
    bool lside = tr[0][1].sdist(tr[0][0]) == tr[1][0].sdist(tr[1][2]);
    bool rside = tr[2][0].sdist(tr[2][2]) == tr[1][1].sdist(tr[1][2]);
    bool dside = tr[3][2].sdist(tr[3][1]) == tr[1][0].sdist(tr[1][1]);
    bool sides = lside && rside && dside;
    return angles && sides;
}
int indicies[4];
int rearrangement[4];

bool test(int i, int j, int k, int m) {
    indicies[0] = i;
    indicies[1] = j;
    indicies[2] = k;
    indicies[3] = m;
    for (rearrangement[0] = 0; rearrangement[0] < 3; ++rearrangement[0]) {
        for (rearrangement[2] = 0; rearrangement[2] < 3; ++rearrangement[2]) {
            for (rearrangement[3] = 0; rearrangement[3] < 3; ++rearrangement[3]) {
                for (int index = 0; index < 4; ++index) {
                    for (int corner = 0; corner < 3; ++corner) {
                        tr[index][corner] = a[indicies[index]][(corner + rearrangement[index]) % 3];
                        tra[index][corner] = an[indicies[index]][(corner + rearrangement[index]) % 3];
                    }
                }
                if (check()) {
                    return true;
                }
            }
        }
    }
    return false;
}

double angle1(int i, int corner) {
    return (a[i][corner == 0 ? 2 : corner - 1] - a[i][corner]).getAngle(a[i][corner == 2 ? 0 : corner + 1] - a[i][corner]);
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        an[i][0] = angle1(i, 0);
        an[i][1] = angle1(i, 1);
        an[i][2] = angle1(i, 2);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                for (int m = 0; m < n; ++m) {
                    arr = {i, j, k, m};
                    sort(arr.begin(), arr.end());
                    if (notSame(i, j, k, m) && test(i, j, k, m)) {
                        answer.insert(arr);
                    }
                }
            }
        }
    }
    cout << answer.size() << '\n';
    for (auto [i, j, k, l] : answer) {
        cout << i + 1 << ' ' << j + 1 << ' ' << k + 1 << ' ' << l + 1 << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    solve();
}
