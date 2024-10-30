#pragma GCC optimize("O3")
#include "bits/extc++.h"
%:define int int64_t
using namespace std;
using namespace __gnu_pbds;
const int MAXN = 1e6 + 1;

array<__uint128_t, 4> g[MAXN];
pair<int, int> repl[MAXN];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct chash {  // large odd number for C
    const __uint128_t C = __uint128_t(4e18 * acos(0)) | 71;
    const __uint128_t RNDD = (__uint128_t)rng();
    __uint128_t operator()(__uint128_t x) const { return __builtin_bswap128((x ^ RNDD) * C); }
};
void solve() {
    int n, m;
    cin >> n >> m;
    uniform_int_distribution<int> dist(10000, 100000000);
    for (int i = 0; i <= n; ++i) {
        repl[i] = {dist(rng), dist(rng)};
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;

        g[a][0] ^= repl[b].first;
        g[a][1] += repl[b].first;
        g[a][2] ^= repl[b].second;
        g[a][3] += repl[b].second;

        g[b][0] ^= repl[a].first;
        g[b][1] += repl[a].first;
        g[b][2] ^= repl[a].second;
        g[b][3] += repl[a].second;
    }
    gp_hash_table<__uint128_t, int, chash> cnt({}, {}, {}, {}, {1 << 20});
    int answer = 0;
    for (int i = 1; i <= n; ++i) {
        __uint128_t ha = (((((g[i][0]) * 100000000000 + g[i][1]) * 100000000000) + g[i][2]) * 100000000000 + g[i][3]);
        int& it = cnt[ha];
        answer += it;
        it++;
    }
    for (int i = 1; i <= n; ++i) {
        g[i][0] ^= repl[i].first;
        g[i][1] += repl[i].first;
        g[i][2] ^= repl[i].second;
        g[i][3] += repl[i].second;
    }
    cnt.clear();
    for (int i = 1; i <= n; ++i) {
        __uint128_t ha = (((((g[i][0]) * 100000000000 + g[i][1]) * 100000000000) + g[i][2]) * 100000000000 + g[i][3]);
        int& it = cnt[ha];
        answer += it;
        it++;
    }
    cout << answer << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
