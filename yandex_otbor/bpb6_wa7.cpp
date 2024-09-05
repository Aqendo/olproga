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
            if (pluses[oddity].find(d) != pluses[oddity].end()) continue;
            int most_left_x = max<int>(d - n, 0);
            int most_left_y = d - most_left_x;
            int most_right_x = min(d, m);
            int most_right_y = d - most_right_x;
            int ans = most_right_x - most_left_x + 1;
            auto from = minuses[oddity].lower_bound(most_right_y - most_right_x);
            auto to = minuses[oddity].upper_bound(most_left_y - most_left_x);
            answer += ans;
            if (from != minuses[oddity].end() && to != minuses[oddity].begin()) {
                to--;
                int delta = (minuses[oddity].order_of_key(*to) - minuses[oddity].order_of_key(*from) + 1);
                answer -= delta;
            }
            pluses[oddity].insert(d);
        } else {
            // y - x = d
            // y = x + d
            // x = y - d
            if (minuses[oddity].find(d) != minuses[oddity].end()) continue;
            int most_right = min(n - d, m);
            int most_left = max<int>(-d, 0);
            int ans = most_right - most_left + 1;
            int height_most_right = most_right + d;
            int height_most_left = most_left + d;
            auto from = pluses[oddity].lower_bound(most_left + height_most_left);
            auto to = pluses[oddity].upper_bound(most_right + height_most_right);
            answer += ans;
            if (from != pluses[oddity].end() && to != pluses[oddity].begin()) {
                to--;
                int delta = (pluses[oddity].order_of_key(*to) - pluses[oddity].order_of_key(*from) + 1);
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
