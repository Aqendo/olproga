#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> pairs(n);
    for (int i = 0; i < n; ++i) {
        cin >> pairs[i].first >> pairs[i].second;
    }
    vector<int> dists(n * (n - 1) / 2);
    int index = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            dists[index++] = abs(pairs[i].first - pairs[j].first) + abs(pairs[i].second - pairs[j].second);
        }
    }
    sort(dists.begin(), dists.end());
    cout << dists[k - 1] << endl;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
