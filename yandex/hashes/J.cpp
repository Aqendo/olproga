#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
template <class K, class V>
using hash_big =
    gp_hash_table<K, V, hash<K>, equal_to<K>, direct_mask_range_hashing<>,
                  linear_probe_fn<>,
                  hash_standard_resize_policy<hash_exponential_size_policy<>,
                                              hash_load_check_resize_trigger<>, true>>;
%:define int int64_t


const int q = 227, p = 239, q1 = 267, p1 = 337, mod1 = 1e9 + 7;
// const int q = 2, p = 3;
const int mod = 1e9 + 9;
vector<vector<int>> h, h1;
int po[502], qo[502], po1[502], qo1[502];
pair<int, int> substr(int x1, int y1, int x2, int y2) {
    return {
        ((h[x2][y2] - h[x2][y1 - 1] * po[y2 - y1 + 1] % mod \
        - h[x1 - 1][y2] * qo[x2 - x1 + 1] % mod + h[x1 - 1][y1 - 1] * po[y2 - y1 + 1] % mod \
        * qo[x2 - x1 + 1] % mod) % mod + mod) % mod,
        ((h1[x2][y2] - h1[x2][y1 - 1] * po1[y2 - y1 + 1] % mod1 \
        - h1[x1 - 1][y2] * qo1[x2 - x1 + 1] % mod1 + h1[x1 - 1][y1 - 1] * po1[y2 - y1 + 1] % mod1 \
        * qo1[x2 - x1 + 1] % mod1) % mod1 + mod1) % mod1
    };
}
int n, m;
array<int, 4> f(int side) {
    map<pair<int32_t, int32_t>, int32_t> hashes;
    for (int i = 1; i + side - 1 <= n; ++i) {
        for (int j = 1; j + side - 1 <= m; ++j) {
            pair<int32_t, int32_t> h_res = substr(i, j, i + side - 1, j + side - 1);
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
    vector<vector<char>> grid(n + 1, vector<char> (m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> grid[i][j];
        }
    }
    h.assign(n + 1, vector<int> (m + 1));
    h1.assign(n + 1, vector<int> (m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            h[i][j] = ((h[i][j - 1] * p % mod + h[i - 1][j] * q % mod \
                - h[i - 1][j - 1] * p % mod * q % mod \
                + grid[i][j]) % mod + mod) % mod;
            h1[i][j] = ((h1[i][j - 1] * p1 % mod1 + h1[i - 1][j] * q1 % mod1 \
                - h1[i - 1][j - 1] * p1 % mod1 * q1 % mod1 \
                + grid[i][j]) % mod1 + mod1) % mod1;
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
    cin.tie(nullptr)->sync_with_stdio(false);
    po[0] = 1;
    qo[0] = 1;
    po1[0] = 1;
    qo1[0] = 1;
    for (int i = 1; i <= 501; ++i) {
        po[i] = (po[i - 1] * p) % mod;
        qo[i] = (qo[i - 1] * q) % mod;
        po1[i] = (po1[i - 1] * p1) % mod1;
        qo1[i] = (qo1[i - 1] * q1) % mod1;
    }
    solve();
}
