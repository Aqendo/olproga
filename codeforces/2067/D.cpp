#include <bits/stdc++.h>
using namespace std;
#define int int64_t

int ask(int x, int y) {
    cout << "? " << x << ' ' << y << endl;
    int answer = 0;
    cin >> answer;
    if (answer == -1) exit(0);
    return answer;
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define uid(x, y) uniform_int_distribution<int>(x, y)(rng)
void solve() {
    int n;
    cin >> n;
    vector<int> x(n);
    map<int, int> cnt;
    int mn = INT_MAX;
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        cnt[x[i]]++;
    }
    int val = -1;
    for (int i = 1; i <= n; ++i) {
        if (cnt[i] == 0) {
            val = i;
        }
    }
    int next = uid(1, n);
    while (next == val) next = uid(1, n);
    if (val == -1) {
        val = max_element(x.begin(), x.end()) - x.begin() + 1;
        next = min_element(x.begin(), x.end()) - x.begin() + 1;
    }
    int a = ask(val, next);
    int b = ask(next, val);
    if (a == 0 || b == 0) {
        cout << "! A" << endl;
        return;
    }
    if (a == b && a >= abs(x[val - 1] - x[next - 1])) {
        cout << "! B" << endl;
        return;
    }
    cout << "! A" << endl;
}

signed main() {
    // cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}
