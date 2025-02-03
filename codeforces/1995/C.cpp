#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 2e5 + 78;

int a[N];

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int last_power = 0;
    int answer = 0;
    for (int i = 1; i < n; ++i) {
        if (a[i] == 1) {
            if (a[i - 1] > a[i]) {
                cout << -1 << '\n';
                return;
            }
        }
        if (a[i - 1] == 1) {
            answer += last_power;
            continue;
        }
        if (a[i - 1] > a[i]) {
            int t = a[i];
            int addition = 0;
            while (t < a[i - 1]) {
                t *= t;
                addition += 1;
            }
            answer += last_power + addition;
            last_power = last_power + addition;
        } else {
            double t = a[i];
            int addition = 0;

            while (sqrt(t) >= a[i - 1]) {
                t = sqrt(t);
                addition += 1;
            }
            answer += max<int>(0, last_power - addition);
            last_power = max<int>(0, last_power - addition);
        }
    }
    cout << answer << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}
