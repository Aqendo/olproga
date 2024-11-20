#include "bits/stdc++.h"
using namespace std;

long long precalc[69];
long long get_len(long long x) {
    return 64 - __builtin_clzll(x);
}
long long get_prefix(long long x, long long how_many) {
    return x >> (get_len(x) - how_many);
}
void get_precalc() {
    long long power = 2;
    precalc[0] = 0;
    for (int i = 1; i < 69; ++i) {
        precalc[i] = precalc[i - 1] + power;
        if (precalc[i] < 0) {
            precalc[i] = (long long)1e18 + 3;
        }
        power <<= 1;
    }
}

long long f(long long n, long long x) {
    if (x == n) return 1;
    long long pref = get_prefix(n, get_len(x));
    long long amount = 0;
    if (x < pref) {
        amount = 1 + precalc[get_len(n) - get_len(x)];
    } else if (x > pref) {
        amount = 1 + precalc[get_len(n) - get_len(x) - 1];
    } else {
        amount = 1 + precalc[get_len(n) - get_len(x) - 1] + n - (x << (get_len(n) - get_len(x))) + 1;
    }
    amount = amount + (x % 2 == 0 ? f(n, x + 1) : 0);
    amount = amount <= 0 ? (long long)1e18 + 3 : amount;
    return amount;
}

long long solve(long long n, long long k) {
    if (n == 1) {
        return 1;
    }
    long long l = 1, r = n / 2;
    while (l != r) {
        long long m = (l + r + 1) >> 1;
        long long res = f(n, m * 2);
        // cout << res << ' ' << m * 2 << endl;
        // cout << res << ' ' << m * 2 << endl;

        if (res >= k) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    long long mx = l * 2;
    if (f(n, mx) < k) mx = 0;
    // cout << mx << endl;
    l = 0, r = n / 2;
    while (l != r) {
        long long m = (l + r + 1) >> 1;
        if (m * 2 + 1 <= n && f(n, m * 2 + 1) >= k) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    if (f(n, l * 2 + 1)) {
        mx = max(mx, l * 2 + 1);
    }
    return mx;
}

long long get_real_answer(long long n, long long k) {
    for (int i = n; i >= 1; --i) {
        long long cnt = 0;
        for (int number_to_get_path = n; number_to_get_path >= 1; --number_to_get_path) {
            long long number = number_to_get_path;
            while (number > 0) {
                if (number == i) {
                    cnt++;
                    break;
                }
                if (number % 2 == 0) {
                    number /= 2;
                    if (number == i) {
                        cnt++;
                        break;
                    }
                } else {
                    number--;
                    if (number == i) {
                        cnt++;
                        break;
                    }
                }
            }
        }
        if (cnt >= k) {
            return i;
        }
    }
    assert(false);
    return 0;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    get_precalc();
    long long n, k;
    cin >> n >> k;
    cout << solve(n, k) << endl;
    // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    // int tc = 0;
    // while (true) {
    //     if (tc++ % 1000 == 0) {
    //         cout << tc << endl;
    //     }
    //     long long n = uniform_int_distribution<int>(300, 400)(rng);
    //     long long k = uniform_int_distribution<int>(1, 10)(rng);
    //     long long real_answer = get_real_answer(n, k);
    //     long long our_answer = solve(n, k);
    //     if (our_answer != real_answer) {
    //         cout << n << ' ' << k << endl;
    //         cout << real_answer << ' ' << our_answer << endl;
    //         return 0;
    //     }
    // }
}
