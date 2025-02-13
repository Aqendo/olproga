#include <bits/stdc++.h>
using namespace std;
#define int int64_t
int koshka(int n, int m, int t) {
    int answ = 0;
    for (int fi = 1; fi <= n; ++fi) {
        answ += min(m, ((2 * t + 1 + 2 * fi) / (2 * fi + 1) - 1) / 2);
    }
    return answ;
}
int me(int n, int m, int t) {
    int answer = 0;
    for (int y = 1; y <= n; ++y) {
        int xmeq = max<int>(1, (t - y + 2 * y) / (2 * y + 1));
        answer += max<int>(0, m - xmeq + 1);
    }
    return answer;
}
void solve() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define uid(x, y) uniform_int_distribution<int>(x, y)(rng)
    while (true) {
        int n = uid(1, 30);
        int m = uid(1, 30);
        int t = uid(1, 10000);
        if (koshka(n, m, t) != me(n, m, t)) {
            cout << n << ' ' << m << ' ' << t << '\n';
            cout << koshka(n, m, t) << ' ' << me(n, m, t) << '\n';
            return;
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
