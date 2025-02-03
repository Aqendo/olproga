#include <bits/stdc++.h>
using namespace std;
#define int int64_t

int sign(int x) {
    if (x < 0) return -1;
    return 1;
}

void solve() {
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        int sum = INT_MAX;
        int answer[3] = {0, 0, 0};
        if (b >= 0 && a + b >= 0) {
            if (a + b < sum) {
                answer[0] = a + b;
                answer[1] = b;
                answer[2] = 0;
            }
        }
        if (-a >= 0 && -a - b >= 0) {
            if ((-a) + (-a - b) < sum) {
                answer[0] = 0;
                answer[1] = -a;
                answer[2] = -a - b;
            }
        }
        if (a >= 0 && -b >= 0) {
            if ((a) + (-b) < sum) {
                answer[0] = a;
                answer[1] = 0;
                answer[2] = -b;
            }
        }
        cout << answer[0] << ' ' << answer[1] << ' ' << answer[2] << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
