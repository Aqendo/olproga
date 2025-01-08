#include <bits/stdc++.h>
#define int int64_t
using namespace std;

struct Dot {
    int x, y;
    int dx, dy;
    int c;
    Dot operator-(const Dot &r) const {
        return {x - r.x, y - r.y};
    }
    int vecmul(const Dot &r) const {
        return x * r.y - y * r.x;
    }
    int squared_len() {
        return x * x + y * y;
    }
};
vector<Dot> dots;
int n, T;
int remain;

int dist(const Dot &l, const Dot &r) {
    return ((l.x - r.x) * (l.x - r.x) + (l.y - r.y) * (l.y - r.y));
}
int getsign(int x) {
    if (x < 0)
        return -1;
    else if (x > 0)
        return 1;
    return 0;
}
bool left_turn(const Dot &B, const Dot &O, const Dot &A) {
    return (A - O).vecmul(B - O) > 0;
}
int f(int t) {
    vector<Dot> nd(n);
    Dot point = {dots[0].x + dots[0].dx * t, dots[0].y + dots[0].dy * t};
    for (int i = 0; i < n; ++i) {
        nd[i] = dots[i];
        nd[i].x += nd[i].dx * t;
        nd[i].y += nd[i].dy * t;
        if (nd[i].x < point.x || (nd[i].x == point.x && nd[i].y < point.y)) {
            point = nd[i];
        }
    }
    if (n > 10000 && remain == n - 2) {
        array<vector<int>, 2> bycol;
        int po = 0;
        for (int i = 0; i < n; ++i) {
            bycol[nd[i].c - 1].push_back(i);
            if (nd[i].c == 2) {
                if (nd[i].x < nd[bycol[1][po]].x || (nd[i].x == nd[bycol[1][po]].x && nd[i].y < nd[bycol[1][po]].y)) {
                    po = (int)bycol[nd[i].c - 1].size() - 1;
                }
            }
        }
        if (bycol[1].empty()) exit(0);
        Dot with_that = nd[bycol[1][po]];
        sort(bycol[1].begin(), bycol[1].end(),
             [&with_that, &nd, &bycol](int p1, int p2) -> bool {
                 Dot OA = nd[p1] - with_that;
                 Dot OB = nd[p2] - with_that;
                 auto vec_res = OA.vecmul(OB);
                 return vec_res > 0 ||
                        (vec_res == 0 && OA.squared_len() < OB.squared_len());
             });
        vector<int> convex = {bycol[1].front()};
        for (int i = 1; i < (int)bycol[1].size(); ++i) {
            while (convex.size() >= 2 &&
                   !left_turn(nd[convex[convex.size() - 2]], nd[convex[convex.size() - 1]],
                              nd[bycol[1][i]])) {
                convex.pop_back();
            }
            convex.push_back(bycol[1][i]);
        }
        int64_t answer = 0;
        for (int i = 0; i < (int)bycol[0].size(); ++i) {
            int l = 0, r = convex.size();
            while (r - l > 3) {
                int m1 = l + (r - l) / 3;
                int m2 = r - (r - l) / 3;
                if (dist(nd[bycol[0][i]], nd[convex[m1]]) < dist(nd[bycol[0][i]], nd[convex[m2]])) {
                    l = m1;
                } else {
                    r = m2;
                }
            }
            for (int j = max<int>(0, l - 500); j <= min((int)convex.size() - 1, r + 500); ++j) {
                // if (dist(nd[bycol[0][i]], nd[convex[j]]) > answer) {
                //     cout << nd[bycol[0][i]].x << ' ' << nd[bycol[0][i]].y << ' ' << nd[convex[j]].x << ' ' << nd[convex[j]].y << endl;
                // }
                answer = max(answer, dist(nd[bycol[0][i]], nd[convex[j]]));
            }
        }
        return answer;
    }
    if (n <= 10000) {
        int answer = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
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
        for (int i = 1; i < n; ++i) {
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
        int l1 = 0, l2 = 0;
        vector<int8_t> visited(convex.size());
#define getnext(i) ((i + 1) % convex.size())
#define getprev(i) ((i - 1 + (int)convex.size()) % convex.size())
        int answer = LLONG_MIN;
        while (l1 < (int)convex.size()) {
            Dot from = convex[getnext(l1)] - convex[l1];
            while (l2 == (int)(getnext(l1)) || l1 == l2 || getsign(from.vecmul(convex[getnext(l2)] - convex[l2])) == getsign(from.vecmul(convex[l2] - convex[getprev(l2)]))) {
                l2 = getnext(l2);
            }
            if (visited[l1]) {
                l1++;
                continue;
            }
            visited[l1] = true;
            answer = max(answer, dist(convex[l1], convex[l2]));
            answer = max(answer, dist(convex[getnext(l1)], convex[l2]));
            if (from.vecmul(convex[getnext(l2)] - convex[l2]) == 0) {
                visited[l2] = true;
                answer = max(answer, dist(convex[l1], convex[getprev(l2)]));
                answer = max(answer, dist(convex[getnext(l1)], convex[getnext(l2)]));
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
    vector<int> already(n + 1);
    for (int i = 0; i < n; ++i) {
        Dot &d = dots[i];
        cin >> d.x >> d.y >> d.dx >> d.dy >> d.c;
        if (!already[d.c]) {
            remain--;
            already[d.c] = true;
        }
    }
    int l = 0, r = T + 1;
    while (r - l > 3) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        if (f(m1) < f(m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    int answer = 1e18;
    for (int i = l; i <= min(T, r); ++i) {
        answer = min(answer, f(i));
    }
    cout << sqrt(answer) << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << setprecision(20);
    int t = 1;
    cin >> t;
    while (t--) solve();
}