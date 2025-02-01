#include <bits/stdc++.h>
using namespace std;
#define int int64_t

array<int, 3> solve(int n, int a, int b) {
    array<int, 3> answer_;
    if (n == 1) {
        return {-1, -1, 0};
    }
    if (a == b) {
        return {-2, -2, n / 2};
    }
    if (abs(a - b) == 1 || (min(a, b) == 1 && max(a, b) == n)) {
        return {-3, -3, (n - 1) / 2};
    }
    int diff1 = max(a, b) - min(a, b) - 1;
    int diff2 = n - diff1 - 2;
    cerr << "DIFFS: " << diff1 << ' ' << diff2 << endl;
    int answer = max(diff1, diff2);
    cerr << "first answer: " << answer << endl;
    if (diff1 > diff2) swap(diff1, diff2);
    answer_ = {diff1, diff2, answer};
    int needed1 = (diff1 + 1) / 2;
    int needed2 = diff1 - needed1;
    cerr << "NEEDED: " << needed1 << ' ' << needed2 << endl;
    if (needed1 > needed2) swap(needed1, needed2);
    int sans = max(2 * needed1, 2 * needed2);
    if (needed1 != needed2) {
        sans += (diff2 - 2 + 1) / 2;
    } else {
        sans += (diff2 + 1) / 2;
    }
    answer_[2] = min(answer, sans);
    int l = diff1, r = diff2 + 1;
    while (r - l > 1) {
        int m = (l + r) >> 1;
        // cout << "M: " << m << ' ' << m + (m - diff1) / 2 << ' ' << diff2 << endl;
        if (m + (m - diff1) / 2 < diff2) {
            l = m;
        } else {
            r = m;
        }
    }
    // cout << r << endl;
    answer_[2] = min(answer_[2], r);
    return answer_;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, a, b;
    cin >> n >> a >> b;
    // if (n == 5 && a == 1 && b == 3) {
    //     cout << 2 << endl;
    //     return 0;
    // }
    // if (n == 7 && a == 3 && b == 1) {
    //     cout << 3 << endl;
    //     return 0;
    // }
    // if (n == 9 && a == 7 && b == 1) {
    //     cout << 4 << endl;
    //     return 0;
    // }
    cout << solve(n, a, b)[2] << endl;
}