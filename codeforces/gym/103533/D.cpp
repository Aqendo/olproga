#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> prefix_sums(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        int temp;
        cin >> temp;
        prefix_sums[i + 1] = prefix_sums[i] + temp;
    }
    int i_min = 0, j_max = 0, i_least = 0;
    for (int j = 1; j < n; ++j) {
        if (prefix_sums[j] <= prefix_sums[i_least]) {
            i_least = j;
        }
        if (prefix_sums[j + 1] - prefix_sums[i_least] >
            prefix_sums[j_max + 1] - prefix_sums[i_min]) {
            i_min = i_least;
            j_max = j;
        }
    }
    cout << prefix_sums[j_max + 1] - prefix_sums[i_min] << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}