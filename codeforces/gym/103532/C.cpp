#include <bits/extc++.h>
using namespace std;

using Int = long long;
using Real = long double;

const Real pi = acosl(-1);
const Real eps = 1e-3;

struct r {
    Real x, y;
    r() {}
    r(Real x, Real y) : x(x), y(y) {}
};

r operator+(const r &lhs, const r &rhs) {
    return r(lhs.x + rhs.x, lhs.y + rhs.y);
}

r operator-(const r &lhs, const r &rhs) {
    return r(lhs.x - rhs.x, lhs.y - rhs.y);
}

Real sqdist(const r &lhs, const r &rhs) {
    return ((lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y));
}

Real dot_prod(const r &lhs, const r &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Real cross_prod(const r &lhs, const r &rhs) {
    return lhs.x * rhs.y - rhs.x * lhs.y;
}

Real getangl(const r &vect1, const r &vect2) {
    return fabsl(atan2l(cross_prod(vect1, vect2), dot_prod(vect1, vect2)));
}

struct tria {
    r a, b, c;
    Real ang1, ang2, ang3;
    Int side1, side2, side3;
    vector<vector<Real>> angs;
    vector<vector<Int>> sides;
    tria() {}
    tria(r a, r b, r c) : a(a), b(b), c(c) {
        side1 = sqdist(a, b);
        side2 = sqdist(b, c);
        side3 = sqdist(a, c);
        ang1 = getangl(b - a, c - a);
        ang2 = getangl(c - b, a - b);
        ang3 = getangl(b - c, a - c);
        sides.push_back({side1, side2, side3});
        angs.push_back({ang1, ang2, ang3});
        sides.push_back({side2, side3, side1});
        angs.push_back({ang2, ang3, ang1});
        sides.push_back({side3, side1, side2});
        angs.push_back({ang3, ang1, ang2});
    }
};

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    int test, n;
    cin >> test >> n;
    vector<tria> trias(n);
    for (int i = 0; i < n; ++i) {
        r a, b, c;
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
        trias[i] = tria(a, b, c);
    }
    set<vector<int>> answ;
    for (int fi = 0; fi < n; ++fi) {
        for (int se = 0; se < n; ++se) {
            for (int th = 0; th < n; ++th) {
                for (int fo = 0; fo < n; ++fo) {
                    if (fi == se || fi == th || fi == fo || se == th || se == fo || th == fo) {
                        continue;
                    }
                    int found = false;
                    for (int d1 = 0; d1 < 3; ++d1) {
                        for (int d2 = 0; d2 < 3; ++d2) {
                            for (int d3 = 0; d3 < 3; ++d3) {
                                for (int d4 = 0; d4 < 3; ++d4) {
                                    if (fabsl(trias[fi].sides[d1][0] - trias[fo].sides[d4][0]) < eps &&
                                        fabsl(trias[se].sides[d2][0] - trias[fo].sides[d4][1]) < eps &&
                                        fabsl(trias[th].sides[d3][0] - trias[fo].sides[d4][2]) < eps &&
                                        fabsl(pi - (trias[fi].angs[d1][0] + trias[se].angs[d2][0] + trias[th].angs[d3][0])) < eps &&
                                        fabsl(pi - (trias[fi].angs[d1][2] + trias[se].angs[d2][2] + trias[fo].angs[d4][2])) < eps &&
                                        fabsl(pi - (trias[fi].angs[d1][1] + trias[th].angs[d3][1] + trias[fo].angs[d4][1])) < eps &&
                                        fabsl(pi - (trias[se].angs[d2][1] + trias[th].angs[d3][2] + trias[fo].angs[d4][0])) < eps) {
                                        found = true;
                                        goto end;
                                    }
                                }
                            }
                        }
                    }
                end:
                    if (found) {
                        vector<int> koshka = {fi + 1, se + 1, th + 1, fo + 1};
                        sort(koshka.begin(), koshka.end());
                        answ.insert(koshka);
                    }
                }
            }
        }
    }
    cout << answ.size() << '\n';
    for (auto &vect : answ) {
        for (auto el : vect) {
            cout << el << ' ';
        }
        cout << '\n';
    }
    return 0;
}
