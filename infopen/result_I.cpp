#include <bits/stdc++.h>
using namespace std;

struct Dot {
    int64_t x, y;
    int64_t dx, dy;
    int64_t c;
    Dot operator-(const Dot &r) const {
        return {x - r.x, y - r.y};
    }
    int64_t vecmul(const Dot &r) const {
        return x * r.y - y * r.x;
    }
    int64_t squared_len() {
        return x * x + y * y;
    }
};
vector<Dot> dots;
int64_t n, T;
int64_t remain;

int64_t dist(const Dot &l, const Dot &r) {
    return ((l.x - r.x) * (l.x - r.x) + (l.y - r.y) * (l.y - r.y));
}
int64_t getsign(int64_t x) {
    if (x < 0)
        return -1;
    else if (x > 0)
        return 1;
    return 0;
}
bool left_turn(const Dot &B, const Dot &O, const Dot &A) {
    return (A - O).vecmul(B - O) > 0;
}
int64_t f(int64_t t) {
    vector<Dot> nd(n);
    Dot point = {dots[0].x + dots[0].dx * t, dots[0].y + dots[0].dy * t};
    for (int64_t i = 0; i < n; ++i) {
        nd[i] = dots[i];
        nd[i].x += nd[i].dx * t;
        nd[i].y += nd[i].dy * t;
        if (nd[i].x < point.x || (nd[i].x == point.x && nd[i].y < point.y)) {
            point = nd[i];
        }
    }
    if (n > 10000 && remain == n - 2) {
        array<vector<int64_t>, 2> bycol;
        int64_t po = 0;
        for (int64_t i = 0; i < n; ++i) {
            bycol[nd[i].c - 1].push_back(i);
            if (nd[i].c == 2) {
                if (nd[i].x < nd[bycol[1][po]].x || (nd[i].x == nd[bycol[1][po]].x && nd[i].y < nd[bycol[1][po]].y)) {
                    po = (int64_t)bycol[nd[i].c - 1].size() - 1;
                }
            }
        }
        if (bycol[1].empty()) exit(0);
        Dot with_that = nd[bycol[1][po]];
        sort(bycol[1].begin(), bycol[1].end(),
             [&with_that, &nd, &bycol](int64_t p1, int64_t p2) -> bool {
                 Dot OA = nd[p1] - with_that;
                 Dot OB = nd[p2] - with_that;
                 auto vec_res = OA.vecmul(OB);
                 return vec_res > 0 ||
                        (vec_res == 0 && OA.squared_len() < OB.squared_len());
             });
        vector<int64_t> convex = {bycol[1].front()};
        for (int64_t i = 1; i < (int64_t)bycol[1].size(); ++i) {
            while (convex.size() >= 2 &&
                   !left_turn(nd[convex[convex.size() - 2]], nd[convex[convex.size() - 1]],
                              nd[bycol[1][i]])) {
                convex.pop_back();
            }
            convex.push_back(bycol[1][i]);
        }
        int64_t answer = 0;
        for (int64_t i = 0; i < (int64_t)bycol[0].size(); ++i) {
            int64_t l = 0, r = convex.size();
            while (r - l > 3) {
                int64_t m1 = l + (r - l) / 3;
                int64_t m2 = r - (r - l) / 3;
                if (dist(nd[bycol[0][i]], nd[convex[m1]]) < dist(nd[bycol[0][i]], nd[convex[m2]])) {
                    l = m1;
                } else {
                    r = m2;
                }
            }
            for (int64_t j = max<int64_t>(0, l - 500); j <= min((int64_t)convex.size() - 1, r + 500); ++j) {
                // if (dist(nd[bycol[0][i]], nd[convex[j]]) > answer) {
                //     cout << nd[bycol[0][i]].x << ' ' << nd[bycol[0][i]].y << ' ' << nd[convex[j]].x << ' ' << nd[convex[j]].y << endl;
                // }
                answer = max(answer, dist(nd[bycol[0][i]], nd[convex[j]]));
            }
        }
        return answer;
    }
    if (n <= 10000) {
        int64_t answer = 0;
        for (int64_t i = 0; i < n; ++i) {
            for (int64_t j = i + 1; j < n; ++j) {
                if (nd[i].c != nd[j].c)
                    answer = max(answer, (nd[i].x - nd[j].x) * (nd[i].x - nd[j].x) + (nd[i].y - nd[j].y) * (nd[i].y - nd[j].y));
            }
        }
        return answer;
    }
    if (remain != n - 2) {
        Dot mx = point;
        sort(nd.begin(), nd.end(),
             [&mx](const Dot &p1, const Dot &p2) -> bool {
                 Dot OA = p1 - mx;
                 Dot OB = p2 - mx;
                 auto vec_res = OA.vecmul(OB);
                 return vec_res > 0 ||
                        (vec_res == 0 && OA.squared_len() < OB.squared_len());
             });
        vector<Dot> convex = {nd.front()};
        for (int64_t i = 1; i < n; ++i) {
            while (convex.size() >= 2 &&
                   !left_turn(convex[convex.size() - 2], convex[convex.size() - 1],
                              nd[i])) {
                convex.pop_back();
            }
            convex.push_back(nd[i]);
        }
        if (convex.size() == 2) {
            return dist(convex[0], convex[1]);
        }
        int64_t l1 = 0, l2 = 0;
        vector<int8_t> visited(convex.size());

        int64_t answer = LLONG_MIN;
        while (l1 < (int64_t)convex.size()) {
            Dot from = convex[((l1 + 1) % convex.size())] - convex[l1];
            while (l2 == (int64_t)(((l1 + 1) % convex.size())) || l1 == l2 || getsign(from.vecmul(convex[((l2 + 1) % convex.size())] - convex[l2])) == getsign(from.vecmul(convex[l2] - convex[((l2 - 1 + (int64_t)convex.size()) % convex.size())]))) {
                l2 = ((l2 + 1) % convex.size());
            }
            if (visited[l1]) {
                l1++;
                continue;
            }
            visited[l1] = true;
            answer = max({answer, dist(convex[l1], convex[l2]), dist(convex[((l1 + 1) % convex.size())], convex[l2])});
            if (from.vecmul(convex[((l2 + 1) % convex.size())] - convex[l2]) == 0) {
                visited[l2] = true;
                answer = max({answer, dist(convex[l1], convex[((l2 - 1 + (int64_t)convex.size()) % convex.size())]), dist(convex[((l1 + 1) % convex.size())], convex[((l2 + 1) % convex.size())])});
            }
            l1++;
        }
        return answer;
    }
    return 0;
}

void solve() {
    cin >> n >> T;
    remain = n;
    dots.assign(n, {0, 0, 0, 0, 0});
    vector<int64_t> already(n + 1);
    for (int64_t i = 0; i < n; ++i) {
        Dot &d = dots[i];
        cin >> d.x >> d.y >> d.dx >> d.dy >> d.c;
        if (!already[d.c]) {
            remain--;
            already[d.c] = true;
        }
    }
    int64_t l = 0, r = T + 1;
    while (r - l > 3) {
        int64_t m1 = l + (r - l) / 3;
        int64_t m2 = r - (r - l) / 3;
        if (f(m1) < f(m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    int64_t answer = 1e18;
    for (int64_t i = l; i <= min(T, r); ++i) {
        answer = min(answer, f(i));
    }
    cout << sqrt(answer) << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << setprecision(20);
    int64_t t = 1;
    cin >> t;
    while (t--) solve();
}