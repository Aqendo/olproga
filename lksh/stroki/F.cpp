#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "w", stdout);
#endif

int p, mod;
static const int MAXN = 100005;

int sub(int a, int b) {
    return a < b ? a - b + mod : a - b;
}

int add(int a, int b) {
    return a + b >= mod ? a + b - mod : a + b;
}

int mult(int a, int b) {
    return (a + 0ll) * b % mod;
}

int powers[MAXN];

struct Hash {
    vector<int> hash;

    void precalc_hash(string& s) {
        hash[0] = 0;
        for (int i = 1; i <= s.size(); ++i) {
            hash[i] = (1ll * hash[i - 1] * p + s[i - 1]) % mod;
        }
    }

    int substr(int l, int r) {
        if (l > r) return 0;
        return sub(hash[r], mult(hash[l - 1], powers[r - l + 1]));
    }

    Hash(string& s) : hash(s.size() + 1) { precalc_hash(s); }
};

void precalc_powers() {
    powers[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        powers[i] = (1ll * powers[i - 1] * p) % mod;
    }
}

bool isPrime(int n) {
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int primes[26] = {157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293};

void gen_mod_and_p() {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> generator(1e9, 2e9);
    mod = generator(rng);
    while (!isPrime(mod)) {
        mod = generator(rng);
    }
    p = primes[uniform_int_distribution<int>(0, 25)(rng)];
}

void solve() {
    string s;
    cin >> s;
    Hash hash(s);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        int len = min(r1 - l1 + 1, r2 - l2 + 1);
        int l = 0, r = len + 1;
        while (r - l > 1) {
            int m = (l + r) >> 1;
            if (hash.substr(l1, l1 + m - 1) == hash.substr(l2, l2 + m - 1)) {
                l = m;
            } else {
                r = m;
            }
        }
        if (l == len) {
            if (r1 - l1 + 1 == r2 - l2 + 1) {
                cout << "=\n";
            } else {
                if (r1 - l1 + 1 > r2 - l2 + 1) {
                    cout << ">\n";
                } else {
                    cout << "<\n";
                }
            }
            continue;
        }
        int index_first = l1 + r - 2;
        int index_second = l2 + r - 2;
        assert(s[index_first] != s[index_second]);
        if (s[index_first] < s[index_second]) {
            cout << "<\n";
        } else {
            cout << ">\n";
        }
        cout << flush;
    }
}

signed main() {
    gen_mod_and_p();
    precalc_powers();
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}