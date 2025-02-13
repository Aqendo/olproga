#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 5e5 + 78;

int a[N];

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    for (int i_ = 0; i_ < q; ++i_) {
        int l, x;
        cin >> l >> x;
        int answer = 0;
        for (int i = l - 1; i < n; ++i) {
            if (x >= a[i]) {
                answer++;
                x--;
            } else {
                break;
            }
        }
        cout << answer << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
