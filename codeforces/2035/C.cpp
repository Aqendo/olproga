#include "bits/stdc++.h"
#define int int64_t
using namespace std;

void solve() {
    int n;
    cin >> n;
    if (n == 5) {
        cout << "5\n2 1 3 4 5\n";
        return;
    } else if (n == 6) {
        cout << "7\n1 2 4 6 5 3\n";
        return;
    } else if (n == 7) {
        cout << "7\n2 4 5 1 3 6 7\n";
        return;
    }
    set<int> nums;
    for (int i = 1; i <= n; ++i) {
        nums.insert(i);
    }
    if (n % 2 == 0) {
        vector<int> answer;
        if (__popcount(n) == 1) {
            cout << (n | (n - 1)) << '\n';
            answer = {1, 3, n - 2, n - 1, n};
        } else {
            cout << ((1ll << (__lg(n) + 1)) - 1) << '\n';
            int from = (1ll << __lg(n)) - 1;
            answer = {1, 3, from - 1, from, n};
        }
        for (int i : answer) {
            nums.erase(i);
        }
        for (int i : nums) {
            cout << i << ' ';
        }
        for (int i : answer) {
            cout << i << ' ';
        }
        cout << '\n';
    } else {
        cout << n << '\n';
        int from = (1ll << __lg(n)) - 1;
        vector<int> answer = {3, 1, from - 1, from, n - 1, n};
        for (int i : answer) {
            nums.erase(i);
        }
        for (int i : nums) {
            cout << i << ' ';
        }
        for (int i : answer) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) solve();
}
