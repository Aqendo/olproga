#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#include "bits/stdc++.h"

using namespace __gnu_pbds;
using namespace std;

template <class T>
using ordered_set = tree<T, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#else
#define debug(...)
#endif

void solve() {
    int n, m;
    cin >> n >> m;
    n--;
    m--;
    int k;
    cin >> k;
    ordered_set<int> pluses[2];
    ordered_set<int> minuses[2];
    int answer = 0;
    for (int i = 0; i < k; ++i) {
        char move;
        int d;
        cin >> move >> d;
        int oddity = (d % 2 + 2) % 2;
        if (move == '+') {
            // y = d - x
            // x = d - y
            // x = d
            d -= 2;
            debug("+", d);
            if (pluses[oddity].find(d) != pluses[oddity].end()) continue;
            int ans = d;
            if (ans > m) ans -= m;
            ans++;
            auto from = minuses[oddity].lower_bound(-d);
            auto to = minuses[oddity].upper_bound(d);
            answer += ans;
            if (from != minuses[oddity].end() && to != minuses[oddity].begin()) {
                to--;
                int delta = (pluses[oddity].order_of_key(*to) - pluses[oddity].order_of_key(*from) + 1);
                debug(delta);
                answer -= delta;
            }
            pluses[oddity].insert(d);
        } else {
            // y - x = d
            // x = y - d
            if (minuses[oddity].find(d) != minuses[oddity].end()) continue;
            int ans = min(n - d, m) - max<int>(-d, 0) + 1;
            auto from = pluses[oddity].lower_bound(abs(d));
            int x_for_overlap_y = n + d;
            int mx_x = min(x_for_overlap_y, m);
            int y_for_mx_x = mx_x - d;
            auto to = pluses[oddity].upper_bound(m + y_for_mx_x);
            debug(d);
            debug(abs(d), m + y_for_mx_x + 1);
            answer += ans;
            debug(ans);
            if (from != pluses[oddity].end() && to != pluses[oddity].begin()) {
                to--;
                int delta = (pluses[oddity].order_of_key(*to) - pluses[oddity].order_of_key(*from) + 1);
                debug(delta);
                answer -= delta;
            }
            minuses[oddity].insert(d);
        }
    }
    cout << answer << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
