// #pragma GCC optimize("Ofast,unroll-loops")
// #include "bits/allocator.h"
// #pragma GCC target("avx2")
#include "bits/stdc++.h"
using namespace std;
%:ifdef SEREGA
auto __fr = freopen("input.txt", "r", stdin);
%:endif
__uint128_t answer[10000003];
int p[10000003];
constexpr void primes_(int n) {
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
            tempans *= cnt + 1;
        }
        answer[num] += (__uint128_t)tempans;
    }
}

unsigned long long get_fast(int r) {
    return (unsigned long long)(answer[r]);
}
void solve() {
    int64_t n;
    cin >> n;
    primes_(n);
    cout << get_fast(n) + (n * (n - 1)) / 2 - (int)(n >= 4) << '\n';
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    solve();
}