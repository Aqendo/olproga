#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<int> solve(const vector<int> &a, const vector<pair<int, int>> &qs) {
    int n = a.size();
    int q = qs.size();
    vector<int> answers(qs.size());
    for (int i_ = 0; i_ < q; ++i_) {
        auto [l, x] = qs[i_];
        int answer = 0;
        for (int i = l - 1; i < n; ++i) {
            if (x >= a[i]) {
                answer++;
                x--;
            } else
                break;
        }
        answers[i_] = answer;
    }
    return answers;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
