#include <bits/stdc++.h>
using namespace std;
#define int int64_t
namespace my {

const int N = 2e3 + 78;

int a[N], pref[N], dp[N][N];
int n, K;

void solve(int _l, int _r, int l, int r, int k) {
    if (l > r) return;
    int t = (l + r) >> 1;
    int opt = _l;
    for (int j = _l; j <= min(_r, t - 1); ++j) {
        int res = dp[j][k - 1] - (n - t + 1) * a[j] + (n - t + 1) * a[t];
        if (res < dp[t][k]) {
            opt = j;
            dp[t][k] = res;
        }
    }
    solve(_l, opt, l, t - 1, k);
    solve(opt, _r, t + 1, r, k);
}

int solve_me(int n_, int k_, const vector<int> &input) {
    for (int i = 0; i <= n_; ++i) {
        for (int j = 0; j <= k_; ++j) {
            dp[i][j] = 1e18;
        }
    }
    n = n_;
    K = k_;
    for (int i = 1; i <= n; ++i) {
        a[i] = input[i - 1];
        pref[i] = pref[i - 1] + a[i];
    }
    sort(a + 1, a + n + 1, greater<int>());

    dp[1][1] = n * a[1] - pref[n];
    for (int k = 1; k <= K; ++k) {
        solve(1, n, 1, n, k);
    }
    int mn = 1e18;
    for (int i = 1; i <= n; ++i) {
        mn = min(mn, dp[i][K]);
    }
    return mn;
}
}  // namespace my
namespace primo {
const int N = 2e3 + 5;

long long a[N], pref[N];
long long dp[N][N];

int solve(int n, int k, const vector<int> &input) {
    for (int i = 1; i <= n; ++i) {
        a[i] = input[i - 1];
    }

    sort(a + 1, a + n + 1);

    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i - 1] + a[i];
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            dp[i][j] = 4e18;
        }
    }

    dp[0][0] = 0;
    function<void(int, int, int, int, int)> daq = [&](int k, int ql, int qr, int tl, int tr) {
        if (ql > qr) return;
        int qm = (ql + qr) >> 1;

        int opt = 1;
        for (int i = tl; i <= min(qm, tr); ++i) {
            if (dp[qm][k] > dp[i - 1][k - 1] + (a[qm] * (qm - i + 1) - pref[qm] + pref[i - 1])) {
                dp[qm][k] = dp[i - 1][k - 1] + (a[qm] * (qm - i + 1) - pref[qm] + pref[i - 1]);
                opt = i;
            }
        }

        daq(k, ql, qm - 1, tl, opt);
        daq(k, qm + 1, qr, opt, tr);
    };

    for (int i = 1; i <= k; ++i) {
        daq(i, 1, n, 1, n);
    }

    return dp[n][k];
}
}  // namespace primo
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define uid(x, y) uniform_int_distribution<int>(x, y)(rng)
    int timer = 0;
    while (true) {
        cerr << ++timer << '\n';
        int n = uid(1, 100);
        int k = uid(1, n);
        vector<int> input(n);
        for (int i = 0; i < n; ++i) {
            input[i] = uid(1, (int)1e9);
        }
        if (my::solve_me(n, k, input) != primo::solve(n, k, input)) {
            cout << "bad solve\n";
            return 0;
        }
    }
}
