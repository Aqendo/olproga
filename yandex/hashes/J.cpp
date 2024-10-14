#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
using namespace __gnu_pbds;
using namespace std;
# define int int64_t
# ifdef SEREGA
# include "/home/ser/olproga/debug.h"
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
# endif

# ifndef SEREGA
# define printf(...)
# define debug(...)
# endif
template <class K, class V>
using hash_big =
    gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>,
                  linear_probe_fn<>,
                  hash_standard_resize_policy<hash_exponential_size_policy<>,
                                              hash_load_check_resize_trigger<>, true>>;
vector<vector<char>> g;
const int MAXN = 501;
int po[MAXN];
int n, m;
int MOD, P;
bool is_prime(int x) {
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) return false;
    }
    return true;
}

void gen_mp() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    MOD = uniform_int_distribution<int>(1e9, 2e9)(rng);
    while (!is_prime(MOD)) {
        MOD = uniform_int_distribution<int>(1e9, 2e9)(rng);
    }
    P = uniform_int_distribution<int>(29, 100)(rng);
    while (!is_prime(MOD)) {
        MOD = uniform_int_distribution<int>(29, 100)(rng);
    }
}
vector<vector<int>> pref_hashes;
int substr(int i, int from, int to) {
    return ((pref_hashes[i][to] - pref_hashes[i][from - 1] * po[to - from + 1]) % MOD + MOD) % MOD;
}
array<int, 4> f(int side) {
    hash_big<int32_t, int32_t> hashes;
    hashes.resize((n - side) * (m - side));
    for (int i = 1; i + side - 1 <= n; ++i) {
        for (int j = 1; j + side - 1 <= m; ++j) {
            int h_res = 0;
            for (int offseti = 0; offseti < side; ++offseti) {
                h_res = ((h_res * po[side]) + substr(i + offseti, j, j + side - 1)) % MOD;
            }
            if (hashes.find(h_res) != hashes.end()) {
                return {hashes[h_res] / m, hashes[h_res] % m, i - 1, j - 1};
            }
            hashes[h_res] = (i - 1) * m + j - 1;
        }
    }
    return {-1, -1, -1, -1};
}



void solve() {
    cin >> n >> m;
    g.assign(n, vector<char> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> g[i][j];
        }
    }
    pref_hashes.assign(n + 1, vector<int> (m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            pref_hashes[i][j] = (pref_hashes[i][j - 1] * P + g[i - 1][j - 1] - 'a' + 1) % MOD;
        }
    }
    map<int, array<int, 4>> cache;
    int l = 0, r = min(n, m) + 1;
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        auto result = f(mid);
        cache[mid] = result;
        if (result[0] != -1) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << l << endl;
    if (l != 0) {
        auto res = cache[l];
        cout << res[0] + 1 << ' ' << res[1] + 1 << endl;
        cout << res[2] + 1 << ' ' << res[3] + 1 << endl;
    }
}

signed main() {
# ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
# endif
    gen_mp();
    po[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        po[i] = (po[i - 1] * P) % MOD;
    }
    solve();
}
