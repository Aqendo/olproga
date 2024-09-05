#include "bits/stdc++.h"

#define int long long
using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
#endif
map<pair<int, int>, int> cache;
int F(int a, int b) {
    if (cache.contains({a, b})) return cache[{a, b}];
    if (b == 0) return 0;
    if (a > b) return cache[{a, b}] = F(a - 1, b) + b;
    return cache[{a, b}] = F(a, b - 1) + a;
}
int F_iter(int a, int b) {
    if (b == 0) return 0;
    int ans = 0;
    while (a != 0 && b != 0) {
        if (a > b) {
            ans += (a - b) * b;
            a = b;
        } else {
            ans += (b - a + 1) * a;
            b = a - 1;
        }
    }
    return ans;
}

int F_constant(int a, int b) {
    if (b == 0) return 0;
    int ans = 0;
    while (a != 0 && b != 0 && a != b) {
        if (a > b) {
            ans += (a - b) * b;
            a = b;
        } else {
            ans += (b - a + 1) * a;
            b = a - 1;
        }
    }
    if (a == 0 || b == 0) return ans;
    return ans + a * a;
}

const int NEEDED = 2'097'152;

void solve() {
    int cnt = 0;
    for (int i = 0; i <= NEEDED; ++i) {
        int l = 1, r = NEEDED;
        while (r - l > 1) {
            int m = (l + r) >> 1;
            if (F_constant(i, m) <= NEEDED) {
                l = m;
            } else {
                r = m;
            }
        }
        cnt += F_constant(i, l) == NEEDED;
        cnt += F_constant(i, l - 1) == NEEDED;
        cnt += F_constant(i, l + 1) == NEEDED;
    }
    cout << cnt << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
