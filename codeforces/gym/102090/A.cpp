#include <bits/stdc++.h>
using namespace std;
#define int int64_t

int solve_slow(int a, int b, int c) {
    vector<int> dp(b + 1, INT_MAX);
    dp[a] = 0;
    for (int i = a + 1; i <= b; ++i) {
        if (i % c == 0) continue;
        if ((i - 1) % c != 0) {
            dp[i] = min(dp[i], dp[i - 1] + 1);
        }
        if ((i - 2) % c != 0) {
            dp[i] = min(dp[i], dp[i - 2] + 1);
        }
    }
    return dp[b];
}
int get(int r, int c) {
    if (r < c) {
        return (r) / 2;
    }
    int mx = (c - 1) / 2;
    int from = r / c * (mx + 1);
    r -= r / c * c;
    return from + (r) / 2;
}
int answer_fast(int a, int b, int c) {
    int answer = 0;
    if (c % 2 == 0) {
        if (a % 2 == 0 && b / c != a / c) a++, answer++;
        return answer + (b - a + 1) / 2;
    } else {
        if (a / c == b / c) return (b - a + 1) / 2;
        if (a / c == b / c - 1) {
            return ((a + c - 1) / c * c - a) / 2 + 1 + (b - b / c * c) / 2;
        }
        // cout << ((a + c - 1) / c * c - a) / 2 << endl;
        // cout << (b - b / c * c) / 2 << endl;
        // cout << (b / c - a / c - 1) << endl;
        // cout << ((c) / 2) << endl;
        int answer = ((a + c - 1) / c * c - a) / 2 + 1 + (b - b / c * c) / 2 + 1 + (b / c - a / c - 1) * ((c) / 2) + max<int>(0, b / c - a / c - 2);
        return answer;
    }
}
// signed main() {
//     cin.tie(nullptr)->sync_with_stdio(false);
//     int a, b, c;
//     cin >> a >> b >> c;
//     cout << max<int>(1, get(b, c) - get(a, c)) << '\n';
// }
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int a, b, c;
    cin >> a >> b >> c;
    cout << answer_fast(a, b, c) << '\n';
    // cout << answer_fast(2, 10, 3);
    // return 0;
    // for (int a = 1; a <= 60; ++a) {
    //     for (int b = a + 1; b <= 60; ++b) {
    //         for (int c = 2; c <= 60; ++c) {
    //             if (a % c == 0 || b % c == 0) continue;
    //             if (solve_slow(a, b, c) != answer_fast(a, b, c)) {
    //                 cout << a << ' ' << b << ' ' << c << endl;
    //                 cout << solve_slow(a, b, c) << ' ' << answer_fast(a, b, c) << '\n';
    //                 cout << get(a - 1, c) << ' ' << get(a, c) << ' ' << get(a + 1, c) << '\n';
    //                 cout << get(b - 1, c) << ' ' << get(b, c) << ' ' << get(b + 1, c) << '\n';
    //                 cout << '\n';
    //             }
    //         }
    //     }
    // }
    // int c = 4;
    // for (int b = 1; b <= 10; ++b) {
    //     cout << b << ": " << get(b, c) << '\n';
    // }
}