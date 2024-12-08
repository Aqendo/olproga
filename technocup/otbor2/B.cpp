#include <bits/stdc++.h>
#define int int64_t
using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    int answer = INT_MAX;
    {
        vector<int> nex1(n + 1, INT_MAX), nex0(n + 1, INT_MAX);
        for (int i = 0; i < n; ++i) {
            if (i != 0) {
                nex1[i] = nex1[i - 1];
                nex0[i] = nex0[i - 1];
            }
            if (s[i] == '1') {
                nex1[i] = i;
            }
            if (s[i] == '0') {
                nex0[i] = i;
            }
        }
        for (int i = 0; i < n - i; ++i) {
            if (i == n - 1 - i) continue;
            if (s[i] == '0') {
                int teleport = n - 1 - i;
                if (nex0[teleport] <= i) continue;
                int delta = teleport - nex0[teleport];
                answer = min(answer, delta);
            } else {
                int teleport = n - 1 - i;
                if (nex1[teleport] <= i) continue;
                int delta = teleport - nex1[teleport];
                answer = min(answer, delta);
            }
        }
    }
    reverse(s.begin(), s.end());
    {
        vector<int> nex1(n + 1, INT_MAX), nex0(n + 1, INT_MAX);
        for (int i = 0; i < n; ++i) {
            if (i != 0) {
                nex1[i] = nex1[i - 1];
                nex0[i] = nex0[i - 1];
            }
            if (s[i] == '1') {
                nex1[i] = i;
            }
            if (s[i] == '0') {
                nex0[i] = i;
            }
        }
        for (int i = 0; i < n - i; ++i) {
            if (i == n - 1 - i) continue;
            if (s[i] == '0') {
                int teleport = n - 1 - i;
                if (nex0[teleport] <= i) continue;
                int delta = teleport - nex0[teleport];
                answer = min(answer, delta);
            } else {
                int teleport = n - 1 - i;
                if (nex1[teleport] <= i) continue;
                int delta = teleport - nex1[teleport];
                answer = min(answer, delta);
            }
        }
    }
    if (answer > n) {
        cout << -1 << endl;
    } else {
        cout << answer << endl;
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}
