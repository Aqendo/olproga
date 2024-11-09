#include "bits/stdc++.h"
#define int int64_t
using namespace std;

void solve() {
    int x, y, k, l;
    cin >> x >> y >> k >> l;
    int lowest = x / k * k;
    int highest = y / k * k;
    int answer = 0;
    if (lowest != highest) {
        int next_ = (x / k + 1) * k;
        int delta = next_ - lowest - l * 2;
        if (delta <= 0) {
            if (lowest - l > x) {
                answer += (lowest - l - x + 2 * l - 1) / (2 * l);
            }
            if (highest + l < y) {
                answer += (y - l - highest + 2 * l - 1) / (2 * l);
            }
            cout << answer;
            return;
        }
        answer += ((delta + 2 * l - 1) / (2 * l)) * (highest / k - lowest / k);
    }
    if (lowest - l > x) {
        answer += (lowest - l - x + 2 * l - 1) / (2 * l);
    }
    if (highest + l < y) {
        answer += (y - l - highest + 2 * l - 1) / (2 * l);
    }
    cout << answer;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
