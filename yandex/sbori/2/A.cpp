#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    vector<int> all_numbers;
    for (int bit = 0; bit < 63; ++bit) {
        int now = (1ll << bit);
        all_numbers.push_back(now);
        for (int next_bit = bit - 1; next_bit >= 0; --next_bit) {
            now |= (1ll << next_bit);
            all_numbers.push_back(now);
        }
    }
    int n;
    cin >> n;
    int answer = 0;
    for (int i = 0; i < (int)all_numbers.size(); ++i) {
        if (all_numbers[i] <= n) {
            answer++;
        } else {
            break;
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