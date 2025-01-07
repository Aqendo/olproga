#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    int answer = (a + b) / n;
    int a1 = n, an = a / n * n;
    if (a1 <= an) {
        answer += (a1 + an) * ((an - a1) / n + 1) / 2;
    }
    answer += ((((a + b) / n * n) - (a + 1 + n - 1) / n * n) / n + 1) * a;
    answer += ((((a + b) / n * n) - (b + 1 + n - 1) / n * n) / n + 1) * b;
    a1 = (b + 1 + n - 1) / n * n, an = (a + b) / n * n;
    if (a1 <= an) {
        answer -= (a1 + an) * ((an - a1) / n + 1) / 2;
    }
    cout << answer << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}