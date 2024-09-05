#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#include "bits/stdc++.h"

using namespace __gnu_pbds;
using namespace std;

template <class T>
using ordered_set = tree<T, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long
#ifdef SEREGA
// #include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif
#define debug(...)

int solve(int n, int m, const vector<pair<char, int>>& qs) {
    n--;
    m--;
    int k = qs.size();
    ordered_set<int> pluses[2];
    ordered_set<int> minuses[2];
    int answer = 0;
    for (int i = 0; i < k; ++i) {
        auto [move, d] = qs[i];
        int oddity = (d % 2 + 2) % 2;
        if (move == '+') {
            // y = d - x
            // x = d - y
            // x = d
            d -= 2;
            debug("+", d);
            if (pluses[oddity].find(d) != pluses[oddity].end()) continue;
            int most_left_x = max<int>(d - n, 0);
            int most_left_y = d - most_left_x;
            int most_right_x = min(d, m);
            int most_right_y = d - most_right_x;
            int ans = most_right_x - most_left_x + 1;
            debug(ans);

            auto from = minuses[oddity].lower_bound(most_right_y - most_right_x);
            auto to = minuses[oddity].upper_bound(most_left_y - most_left_x);
            answer += ans;
            if (from != minuses[oddity].end() && to != minuses[oddity].begin()) {
                to--;
                int delta = (minuses[oddity].order_of_key(*to) - minuses[oddity].order_of_key(*from) + 1);
                debug(delta);
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
            debug(ans);
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
    return answer;
}
#undef SEREGA
#define uid(x, y) uniform_int_distribution<int>(x, y)(rng)
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        int n = uid(3, 30);
        int m = uid(3, 30);
        int q = uid(1, 10);
        vector<pair<char, int>> qs(q);
        for (int i = 0; i < q; ++i) {
            char move = "+-"[uid(0, 1)];
            if (move == '+') {
                qs[i] = {move, uid(2, n + m)};
            } else {
                qs[i] = {move, uid(1 - m, n - 1)};
            }
        }
        int answer = solve(n, m, qs);
        int real = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                bool good = false;
                for (auto [move, d] : qs) {
                    if (move == '+') {
                        // x + y = d
                        // x = d - y
                        if (j == d - i) {
                            good = true;
                            break;
                        }
                    } else {
                        // y - x = d
                        // y = x + d
                        if (i == j + d) {
                            good = true;
                            break;
                        }
                    }
                }
                real += good;
            }
        }
        if (answer != real) {
            cout << "answer is not real\n";
            cout << answer << ' ' << real << '\n' << '\n';
            cout << n << ' ' << m << '\n' << q << '\n';
            for (auto [move, d] : qs) {
                cout << move << " " << d << '\n';
            }
            return 0;
        }
    }
}
