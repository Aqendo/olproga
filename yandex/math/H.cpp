#pragma GCC optimize("Ofast,unroll-loops")
#include "bits/allocator.h"
#pragma GCC target("avx2")
#include "bits/stdc++.h"
using namespace std;
%:ifdef SEREGA
auto __fr = freopen("input.txt", "r", stdin);
%:endif
__uint128_t answer[5000003];
int p[5000003];
constexpr void primes(int n) {
    vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (p[i] == 0) {
            p[i] = i;
            primes.push_back(i);
        }
        for (int x : primes) {
            if (x > p[i] || 1ll * x * i > n) break;
            p[x * i] = x;
        }
    }
    for (int num = 1; num <= n; ++num) {
        int x = num;
        vector<pair<int, int>> fact = {{1, 1}};
        answer[num] = answer[num - 1];
        while (x != 1) {
            if (fact.back().first == p[x]) {
                fact.back().second++;
            } else {
                fact.push_back({p[x], 1});
            }
            x /= p[x];
        }
        unsigned long long tempans = 1;
        for (auto& [del, cnt] : fact) {
            if (del == 1) continue;
            unsigned long long to_add = 0;
            unsigned long long power_p = del;
            for (int s3 = 0; s3 < cnt; ++s3) {
                to_add += tempans * power_p;
                power_p *= del;
            }
            tempans += to_add;
        }
        answer[num] += (__uint128_t)tempans;
        // cout << num << ": " << (unsigned long long)(answer[num] - answer[num - 1]) << endl;
        // if (num <= 30) {
        //     cout << num << ": " << (unsigned long long)(answer[num] - answer[num - 1]) << endl;
        // }
    }
}

unsigned long long slow_ans = 0;
void factorize(int x) {
    // cout << "factorizing " << x << ": ";
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            // cout << i << ' ';
            slow_ans += i;
            if (i != x / i) {
                // cout << x / i << ' ';
                slow_ans += x / i;
            }
        }
    }
    // cout << x << ' ' << 1 << endl;
    slow_ans += (x != 1 ? x : 0) + 1;
}
unsigned long long get_slow(int l, int r) {
    slow_ans = 0;
    for (int i = l; i <= r; ++i) {
        factorize(i);
    }
    return slow_ans;
}
unsigned long long get_fast(int l, int r) {
    return (unsigned long long)(answer[r] - answer[l - 1]);
}
void solve() {
    int n = 5000001;
    primes(n);
    // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    // while (true) {
    //     int l = uniform_int_distribution<int>(1, 10)(rng);
    //     int r = uniform_int_distribution<int>(l, l + 10)(rng);
    //     if (get_slow(l, r) != get_fast(l, r)) {
    //         cout << l << ' ' << r << endl;
    //         cout << get_slow(l, r) << ' ' << get_fast(l, r) << endl;
    //         return;
    //     }
    // }

    int l, r;
    while (cin >> l >> r) {
        cout << get_fast(l, r) << '\n';
    }
}

void solve_slow() {
    int l, r;
    while (cin >> l >> r) {
        cout << get_slow(l, r) << '\n';
    }
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
}
