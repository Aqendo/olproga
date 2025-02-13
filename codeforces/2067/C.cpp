#include <bits/stdc++.h>
using namespace std;
#define int int64_t

bool has_7(int n) {
    while (n > 0) {
        if (n % 10 == 7) return true;
        n /= 10;
    }
    return false;
}

void solve() {
    int n;
    cin >> n;
    if (has_7(n)) {
        cout << 0 << '\n';
        return;
    }
    int nines = 9;
    int answer = 7;
    for (int i = 1; i <= 10; ++i) {
        for (int count = 1; count <= 7; ++count) {
            if (has_7(n + nines * count)) {
                answer = min<int>(answer, count);
                break;
            }
        }
        nines = 10 * nines + 9;
    }
    for (int i = 1; i <= 10; ++i) {
        if (has_7(n + 9 * i)) {
            answer = min(answer, i);
        }
    }
    cout << answer << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}
