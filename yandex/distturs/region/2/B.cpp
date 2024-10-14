#include "bits/stdc++.h"
using namespace std;
#define int int64_t
# ifdef SEREGA
# include "/home/ser/olproga/debug.h"
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
# endif

# ifndef SEREGA
# define printf(...)
# define debug(...)
# endif

struct Query {
    int l, r, d;
};

int n, k, c, q;
void solve() {
    cin >> n >> k >> c;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    cin >> q;
    vector<Query> qs(q); 
    for (int i = 0; i < q; ++i) {
        cin >> qs[i].l >> qs[i].r >> qs[i].d;
    }
    auto check = [&qs, &a](int cnt) -> bool {
        vector<int> result(n + 2);
        for (int i = 1; i <= n; ++i) {
            result[i] += a[i];
            result[i + 1] -= a[i];
        }
        for (int i = 0; i < cnt; ++i) {
            result[qs[i].l] += qs[i].d;
            result[qs[i].r + 1] -= qs[i].d;
        }
        vector<int> res_p(n + 1);
        for (int i = 1; i <= n; ++i) {
            res_p[i] = res_p[i - 1] + result[i];
        }
        vector<int> pref(n + 1);
        for (int i = 1; i <= n; ++i) {
            pref[i] = pref[i - 1] + res_p[i];
        }
        int i_least = 0, i_min = 0, j_max = 0;
        for (int i = 1; i < n; ++i) {
            if (pref[i] >= pref[i_least]) {
                i_least = i;
            }
            if (pref[i + 1] - pref[max(i + 1 - k, i_least)] < pref[j_max + 1] - pref[i_min]) {
                i_min = max(i + 1 - k, i_least);
                j_max = i;
            }
        }
        int s = pref[j_max + 1] - pref[i_min];
        debug(cnt);
        debug(s);
        debug(res_p);
        return s <= c;
    };
    int l = 0, r = q + 1;
    while (r - l > 1) {
        int m = (l + r) >> 1;
        if (check(m)) {
            l = m;
        } else {
            r = m;
        }
    }
    for (int i = 0; i < l; ++i) {
        cout << "YES\n";
    }
    for (int i = 0; i < q - l; ++i) {
        cout << "NO\n";
    }

}

signed main() {
# ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
# endif
    solve();
}
