#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    int A, B, C;
    cin >> A >> B >> C;
    int T;
    cin >> T;
    vector<int> superfast(m);
    for (int i = 0; i < m; ++i) {
        cin >> superfast[i];
        superfast[i]--;
        if (superfast[i] * B > T) {
            superfast.resize(i);
            m = i;
            break;
        }
    }
    superfast.push_back(n);
    // cout << "M: " << m << endl;
    int answer = m - 1;
    vector<int> remain;
    for (int i = 1; i < m + 1; ++i) {
        int from = superfast[i - 1], to = superfast[i];
        int delta = to - from - 1;
        // cout << "delta: " << delta << endl;
        if (delta <= 0) continue;
        if (from * B + A * delta <= T) {
            // cout << "from * B + A * delta <= T\n";
            answer += delta;
            continue;
        }
        int mx = (T - from * B) / A;
        answer += mx;
        int from_dop = from + mx + 1, to_dop = to - 1;
        // cout << "mx: " << mx << endl;
        // cout << "from_dop : " << from_dop << endl;
        // cout << "to_dop : " << to_dop << endl;

        if (from_dop > to_dop) continue;
        int timer = 0;
        for (from_dop = from + mx + 1; from_dop <= to - 1;) {
            timer++;
            if (timer - 2 > k - m) break;
            // cout << "from_dop: " << from_dop << endl;
            if (from * B + (from_dop - from) * C > T) {
                // cout << "bigger\n";
                break;
            }
            if (from * B + (from_dop - from) * C + (to_dop - from_dop) * A <= T) {
                // cout << "from * B + (from_dop - from) * C + (to_dop - from_dop) * A <= T" << endl;
                // cout << (to_dop - from_dop + 1) << endl;
                remain.push_back(to_dop - from_dop + 1);
                break;
            }
            mx = (T - from * B - (from_dop - from) * C) / A;
            // cout << "MCS: " << from_dop << ' ' << mx << endl;
            remain.push_back(mx + 1);
            from_dop += mx + 1;
        }
    }
    if (remain.empty()) {
        cout << answer << '\n';
        return;
    }
    sort(remain.rbegin(), remain.rend());
    for (int i = 0; i < min<int>(remain.size(), k - m); ++i) {
        answer += remain[i];
    }
    cout << answer << endl;
}
/*
from + A * cnt <= T
cnt <= (T - from) / A

from * B + cnt * C <= T
cnt <= (T - from * B) / C
*/
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    while (t--) solve();
}