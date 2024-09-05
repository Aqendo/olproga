#include "bits/stdc++.h"

using namespace std;
#define int long long
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif
struct Node {
    int x, start, end;
};
string to_string(const Node& n) {
    return "(" + to_string(n.x) + ": [" + to_string(n.start) + ".." + to_string(n.end) + "])";
}
void solve() {
    int n;
    cin >> n;
    map<int, set<int>> indicies_;
    for (int i = 0; i < n; ++i) {
        int x, t;
        cin >> x >> t;
        indicies_[t].insert(x);
    }
    int index = 0;
    vector<Node> indicies(indicies_.size() + 1);
    indicies[index].start = 0;
    indicies[index].end = 0;
    index++;
    for (auto& [u, v] : indicies_) {
        indicies[index].x = u;
        indicies[index].start = *v.begin();
        indicies[index].end = *v.rbegin();
        index++;
    }
    vector<int> dp(2);
    indicies.push_back({-1, 0, 0});
    for (int i = 1; i < indicies.size(); ++i) {
        vector<int> dp_new(2);
        int len = indicies[i].end - indicies[i].start;
        Node& prev = indicies[i - 1];
        Node& now = indicies[i];
        dp_new[0] = dp[0] + abs(prev.start - now.end) + len;
        dp_new[0] = min(dp_new[0], dp[1] + abs(prev.end - now.end) + len);
        dp_new[0] = min(dp_new[0], dp[0] + abs(prev.start - now.start) + 2 * len);

        dp_new[1] = dp[1] + abs(prev.end - now.start) + len;
        dp_new[1] = min(dp_new[1], dp[0] + abs(prev.start - now.start) + len);
        dp_new[1] = min(dp_new[1], dp[1] + abs(prev.end - now.end) + 2 * len);

        dp[0] = dp_new[0];
        dp[1] = dp_new[1];
    }
    cout << dp[0] << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
