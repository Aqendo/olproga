#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    set<int> free_indicies;
    vector<int> used(n);
    used[0] = true;
    for (int i = 2; i < n; ++i) {
        free_indicies.insert(i);
    }
    vector<int> indicies(n - 1);
    iota(indicies.begin(), indicies.end(), 1);
    sort(indicies.begin(), indicies.end(), [&a](int i, int j) { return a[i] > a[j]; });
    for (int i : indicies) {
        auto it_free = free_indicies.lower_bound(i);
        if (it_free == free_indicies.end()) continue;
        auto it_free_next = next(it_free);
        if (it_free_next == free_indicies.end()) continue;
        used[i] = true;
        free_indicies.erase(it_free);
        free_indicies.erase(it_free_next);
    }
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(")("[used[i]]);
    }
    cout << s << '\n';
}
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
