
#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define fi first
#define se second

bool is_covering(auto &this_, auto &coversthat) {
    return abs(this_.fi - coversthat.fi) <= this_.se - coversthat.se;
}
const int INF = 1e9 + 7;
void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> dots(n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        dots[i] = {a + b, -a + b};
    }
    dots.reserve(1000);
    cout << dots[dots.size()].first << endl;
    sort(dots.begin(), dots.end(), [](const auto &l, const auto &r) {
        if (l.fi != r.fi) return l.fi > r.fi;
        return l.se > r.se;
    });
    pair<int, int> now = {-INF, -INF};
    int cnt = 0;
    for (auto &[a, b] : dots) {
        // cout << a << ' ' << b << '\n';
        if (a <= now.fi && b <= now.se) {
            continue;
        }
        cnt++;
        now = {a, b};
    }
    cout << cnt << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}