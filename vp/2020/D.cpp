#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define int int64_t
void solve() {
    int n, q;
    cin >> n >> q;
    pair<int, int> queries[q];
    int last[n + 1];
    iota(last, last + n + 1, int(INT_MAX));
    for (int i = 0; i < q; ++i) {
        string s;
        cin >> s;
        queries[i].first = s == "add";
        cin >> queries[i].second;
        if (s != "add") {
            last[queries[i].second] = i;
        }
    }
    oset<int> stall;
    oset<int> stnot;
    int answer = 0;
    for (int i = 0; i < q; ++i) {
        auto [move, x] = queries[i];
        if (move == 1) {
            int cnt_if_end = 2 * stnot.order_of_key(last[x]);
            // но тут нельзя учитывать те элементы которые не выходят
            int cnt_if_start = last[x] <= int(INT_MAX) ? 2 * ((int)stall.size() - stall.order_of_key(last[x])) : 0;
            answer += 1 + min(cnt_if_end, cnt_if_start);
            stall.insert(last[x]);
            if (last[x] < int(INT_MAX)) {
                answer += 1;
                stnot.insert(last[x]);
            }
        } else {
            stall.erase(i);
            stnot.erase(i);
        }
    }
    cout << answer << '\n';
}
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
