#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int WAKEUP = -1, COMMAND = 0, SINGLE = 1, SLEEP = 2;
const int INF = 1e15;

struct Event {
    int type;
    int l, r;
};
string getname(int type) {
    switch (type) {
        case -1:
            return "WAKEUP";
        case 0:
            return "COMMAND";
        case 1:
            return "SINGLE";
        case 2:
            return "SLEEP";
        default:
            return "UNKNOWN";
    }
}

ostream &operator<<(ostream &out, const Event &r) {
    out << "(" << getname(r.type) << "; [" << r.l << ";" << r.r << "])";
    return out;
}
void solve() {
    int n, d, t;
    cin >> n >> d >> t;
    vector<Event> e;
    e.push_back({.type = WAKEUP,
                 .l = 0,
                 .r = 0});
    for (int i = 0; i < n; ++i) {
        int l, r, x;
        cin >> l >> r >> x;
        e.push_back({.type = x,
                     .l = l,
                     .r = r});
    }
    e.push_back({.type = SLEEP,
                 .l = d,
                 .r = d});

    sort(e.begin(), e.end(), [](auto &l, auto &r) {
        return l.l < r.l;
    });

    n = e.size();
    vector<array<int, 2>> dp(n);

    // 0 - home, 1 - in club
    dp[0][1] = -INF;

    // auto get_nearest_i = [&e](int mx_index, int max_r) -> int {
    //     int l = 0, r = mx_index + 1;
    //     while (r - l > 1) {
    //         int m = (l + r) >> 1;
    //         if (e[m].r <= max_r) {
    //             l = m;
    //         } else {
    //             r = m;
    //         }
    //     }
    //     return l;
    // };
    // for (int i = 0; i < n; ++i) {
    //     cout << e[i] << endl;
    // }
    for (int i = 1; i < n; ++i) {
        // cout << e[i] << endl;
        if (e[i].type == COMMAND) {
            dp[i][0] = -INF;
            dp[i][1] = dp[i - 1][1];
            if (e[i].l - e[i - 1].r >= 2 * t) {
                dp[i][1] += e[i].l - e[i - 1].r - 2 * t;
            }
            if (e[i - 1].r + t <= e[i].l) {
                dp[i][1] = max(dp[i][1], dp[i - 1][0] + (e[i].l - e[i - 1].r - t));
            }
            // cout << dp[i][0] << ' ' << dp[i][1] << endl;
        } else if (e[i].type == SINGLE || e[i].type == SLEEP) {
            dp[i][0] = dp[i - 1][0] + (e[i].r - e[i - 1].r);
            dp[i][1] = dp[i - 1][1];
            if (e[i].l - e[i - 1].r >= 2 * t) {
                dp[i][1] += e[i].l - e[i - 1].r - 2 * t;
            }
            if (e[i - 1].r + t <= e[i].l) {
                dp[i][0] = max(dp[i][0], dp[i - 1][1] + (e[i].r - e[i - 1].r - t));
                dp[i][1] = max(dp[i][1], dp[i - 1][0] + (e[i].l - e[i - 1].r - t));
            }
            // cout << dp[i][0] << ' ' << dp[i][1] << endl;
        }
    }
    // for (int i = 0; i < n; ++i) {
    //     cout << dp[i][0] << ' ' << dp[i][1] << endl;
    // }
    cout << dp[n - 1][0] << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}