#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

int p, mod1, mod2;
static const int MAXN = 30005;

int sub(int a, int b, int mod) {
    return a < b ? a - b + mod : a - b;
}

int add(int a, int b, int mod) {
    return a + b >= mod ? a + b - mod : a + b;
}

int mult(int a, int b, int mod) {
    return (a + 0ll) * b % mod;
}

int powers1[MAXN], powers2[MAXN];

struct Hash1 {
    vector<int> hash;

    void precalc_hash(string& s) {
        if (hash.empty()) {
            hash.assign(s.size() + 2, {});
        }
        hash[0] = 0;
        for (int i = 1; i <= s.size(); ++i) {
            hash[i] = (1ll * hash[i - 1] * p + s[i - 1]) % mod1;
        }
    }

    int substr(int l, int r) {
        if (l > r) return 0;
        return sub(hash[r], mult(hash[l - 1], powers1[r - l + 1], mod1), mod1);
    }

    Hash1(string& s) : hash(s.size() + 1) { precalc_hash(s); }

    Hash1() = default;
};

struct Hash2 {
    vector<int> hash;

    void precalc_hash(string& s) {
        if (hash.empty()) {
            hash.assign(s.size() + 2, {});
        }
        hash[0] = 0;
        for (int i = 1; i <= s.size(); ++i) {
            hash[i] = (1ll * hash[i - 1] * p + s[i - 1]) % mod2;
        }
    }

    int substr(int l, int r) {
        if (l > r) return 0;
        return sub(hash[r], mult(hash[l - 1], powers2[r - l + 1], mod2), mod2);
    }

    Hash2(string& s) : hash(s.size() + 1) { precalc_hash(s); }

    Hash2() = default;
};

void precalc_powers() {
    powers1[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        powers1[i] = (1ll * powers1[i - 1] * p) % mod1;
    }

    powers2[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        powers2[i] = (1ll * powers2[i - 1] * p) % mod2;
    }
}

bool isPrime(int n) {
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int primes[26] = {157, 163, 167, 173, 179, 181, 191, 193, 197,
                  199, 211, 223, 227, 229, 233, 239, 241, 251,
                  257, 263, 269, 271, 277, 281, 283, 293};

int gen_mod_and_p() {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> generator(1e9, 2e9);
    int mod = generator(rng);
    while (!isPrime(mod)) {
        mod = generator(rng);
    }
    p = primes[uniform_int_distribution<int>(0, 25)(rng)];
    return mod;
}

Hash1 h1_first, h2_first;
Hash2 h1_second, h2_second;
vector<int> cache;

bool check(string& a, string& b, int len) {
    set<pair<int, int>> hashes;
    if (len == 0) return true;
    if (cache[len] != -1) return cache[len];
    for (int i = 1; i + len - 1 <= a.size(); ++i) {
        hashes.insert({h1_first.substr(i, i + len - 1),
                       h1_second.substr(i, i + len - 1)});
    }
    for (int j = 1; j + len - 1 <= b.size(); ++j) {
        if (hashes.contains({h2_first.substr(j, j + len - 1),
                             h2_second.substr(j, j + len - 1)})) {
            cache[len] = true;
            return true;
        }
    }
    cache[len] = false;
    return false;
}

void solve() {
    string a, b;
    cin >> a >> b;
    h1_first.precalc_hash(a);
    h1_second.precalc_hash(a);
    h2_first.precalc_hash(b);
    h2_second.precalc_hash(b);

    cache.assign(min(a.size(), b.size()) + 1, -1);
    int l = 0, r = min(a.size(), b.size()) + 1;
    while (r - l > 1) {
        int m = (l + r) >> 1;
        if (check(a, b, m)) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << l << ' ';
}

signed main() {
    mod1 = gen_mod_and_p();
    mod2 = gen_mod_and_p();
    precalc_powers();
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
