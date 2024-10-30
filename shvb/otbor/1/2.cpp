#ifndef SEREGA
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define all(x) (x).begin(), (x).end()

void solve() {
    int n;
    cin >> n;
    vector<pair<int, string>> guys(n);
    for (int i = 0; i < n; ++i) {
        cin >> guys[i].second >> guys[i].first;
    }
    sort(all(guys));
    int last = 0;
    vector<string*> answer(n);
    int index = 0;
    for (int i = 0; i < n; i += 2) {
        last = i;
        answer[i] = &guys[index++].second;
    }
    if (last == n - 1) {
        last--;
    } else {
        last++;
    }
    for (int i = last; i >= 0; i -= 2) {
        answer[i] = &guys[index++].second;
    }
    for (int i = 0; i < n; ++i) {
        cout << *answer[i] << ' ';
    }
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}