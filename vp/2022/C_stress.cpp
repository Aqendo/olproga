#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 10005;

namespace koshka {
const int MAX = 10005;
vector<int> dels[MAX];
int mindel[MAX];
int dp[MAX];
void init() {
    fill(mindel, mindel + MAX, 2e9);
    for (int i = 2; i < MAX; ++i) {
        if (mindel[i] != 2e9) {
            continue;
        }
        for (int j = 2 * i; j < MAX; j += i) {
            mindel[j] = min(mindel[j], i);
        }
    }
    for (int i = 0; i < MAX; ++i) {
        dels[i].reserve(40);
    }
    for (int i = 1; i < MAX; ++i) {
        for (int j = i; j < MAX; j += i) {
            dels[j].push_back(i);
        }
    }
}
int get(int n, int k, const vector<int> &arr) {
    vector<int> gen;
    for (auto el : arr) {
        for (auto ee : dels[el]) {
            gen.push_back(ee);
        }
    }
    sort(gen.begin(), gen.end());
    gen.erase(unique(gen.begin(), gen.end()), gen.end());
    int le = -1, ri = gen.size();
    while (ri - le > 1) {
        auto _mi = le + (ri - le) / 2;
        auto mi = gen[_mi];
        for (int i = 0; i < MAX; ++i) {
            if (i <= mi) {
                dp[i] = 0;
            } else {
                dp[i] = 2e9;
            }
        }
        for (int i = mi + 1; i < MAX; ++i) {
            for (auto el : dels[i]) {
                dp[i] = min(dp[i], dp[i / el] + el);
            }
        }
        int cur = 0;
        for (auto el : arr) {
            cur += dp[el];
        }
        if (cur <= k) {
            ri = _mi;
        } else {
            le = _mi;
        }
    }
    return gen[ri];
}
}  // namespace koshka
namespace me {
int a[N];
int n, k;

vector<int> fact[N];
int lp[N];
int s[N];
vector<int> pr;

int f(int mx) {
    int left = k;
    for (int i = 0; i < n; ++i) {
        int mn = INT_MAX;
        if (a[i] <= mx) continue;
        for (int j : fact[i]) {
            if (a[i] / j <= mx) {
                mn = min(mn, s[j]);
            }
        }
        if (mn <= left) {
            left -= mn;
        } else {
            return false;
        }
    }
    return true;
}
void init() {
    for (int i = 2; i < N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        int val = i;
        while (val > 1) {
            s[i] += lp[val];
            val /= lp[val];
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] < N; ++j) {
            lp[i * pr[j]] = pr[j];
        }
    }
}
int solve(int n_, int k_, const vector<int> &arr) {
    n = n_;
    k = k_;
    for (int i = 0; i < n; ++i) {
        fact[i].clear();
    }
    for (int i = 0; i < n; ++i) {
        a[i] = arr[i];
        for (int j = 1; j * j <= a[i]; ++j) {
            if (a[i] % j == 0) {
                fact[i].push_back(j);
                if (a[i] / j != j) {
                    fact[i].push_back(a[i] / j);
                }
            }
        }
    }
    int l = 0, r = 1e6 + 1;
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        if (f(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return r;
}
}  // namespace me

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define uid(x, y) uniform_int_distribution<int>(x, y)(rng)
    koshka::init();
    me::init();
    int timer = 0;
    while (true) {
        cerr << ++timer << '\n';
        int n = uid(1, 100);
        int k = uid(1, 100000);
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = uid(1, 10000);
        }
        int kshk = koshka::get(n, k, arr);
        int mee = me::solve(n, k, arr);
        if (kshk != mee) {
            cout << n << ' ' << k << '\n';
            for (int i : arr) {
                cout << i << ' ';
            }
            cout << '\n';
            cout << kshk << ' ' << mee << '\n';
            return 0;
        }
    }
}
