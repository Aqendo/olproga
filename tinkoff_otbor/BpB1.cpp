#include "bits/stdc++.h"

using namespace std;
#define int long long
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif
vector<int> cnts = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
//                  0  1  2  3  4  5  6  7  8  9
void solve() {
    int n, k;
    cin >> n >> k;
    set<int> inputs;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        inputs.insert(t);
    }
    if (inputs.contains(9)) {
        inputs.erase(6);
        inputs.erase(0);
    }
    if (inputs.contains(6)) {
        inputs.erase(0);
    }
    if (inputs.contains(5)) {
        inputs.erase(3);
        inputs.erase(2);
    }
    vector<int> items;
    vector<int> numbers(inputs.begin(), inputs.end());
    sort(numbers.begin(), numbers.end(), [](auto& p1, auto& p2) { return cnts[p1] < cnts[p2]; });
    for (int i : numbers) {
        items.push_back(cnts[i]);
    }
    vector<int> dp(n + 1, INT_MIN);
    vector<int> prev(n + 1, -1);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < items.size(); ++j) {
            if (i - items[j] < 0) continue;
            if (dp[i - items[j]] >= 0) {
                if (dp[i - items[j]] + 1 > dp[i]) {
                    dp[i] = dp[i - items[j]] + 1;
                    prev[i] = j;
                }
            }
        }
    }
    vector<int> result;
    int cur = n;
    while (prev[cur] != -1) {
        result.push_back(numbers[prev[cur]]);
        cur -= items[prev[cur]];
    }
    sort(result.rbegin(), result.rend());
    for (int i : result) {
        cout << i;
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
